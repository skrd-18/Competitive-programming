# EE2028 tutorial notes → what to actually read

Your roadmap gives EE2028 about **3 hours on Thursday morning** (09:00–12:00).
The tutorial pack is 34 pages. Here's what earns its place in those 3 hours.

> **Note:** only `EE2028TUTORIALNOTES.pdf` came through — the "EE2028 Summary
> Rachelle" file didn't attach. Re-upload it if you want it folded in.

---

## The one-line answer

**Read Tutorial 5 (Interrupts & NVIC) properly, Tutorial 3 (GPIO) properly, and
Tutorial 6 Q2/Q3/Q4/Q7 (UART) plus Tutorial 4 Q5 (driver efficiency). Skip
Tutorials 1 and 2 and every board-specific MCQ entirely.**

That's roughly 8 pages out of 34, and it covers close to all of the interview
value in the pack.

---

## 🔴 Tier 1 — Tutorial 5: Interrupts and NVIC · **90 minutes**

Interrupts are the single most-asked embedded interview topic anywhere, and this
tutorial is unusually good. Read all seven questions.

**The highest-value item in your entire EE2028 pack is Q6** — *"Will the ISR for
a particular interrupt always take the same duration to execute?"* The model
answer hands you the term **WCET (worst-case execution time)** and the reasoning:
duration varies because of different trigger conditions, data-dependent branches,
and loops with variable iteration counts — so you compute an upper bound, keep it
low, and avoid blocking code (`delay()`, waiting on a condition) inside a handler.

Saying *"I'd characterise the handler's WCET and keep it bounded"* is a
senior-sounding sentence. Most candidates just say "keep ISRs short."

**Also take from this tutorial:**

- **Q3 — vector table addressing.** Exception number 40 → `40 × 4 = 0xA0`. Each
  vector is 4 bytes because addresses are 32-bit. Pairs with the fact already in
  your playbook that **the first table entry is the initial stack pointer, not a
  handler** — which the notes' own quiz asks about too.
- **Q1/Q2 — priority grouping.** Learn the *concept*: priority splits into
  **pre-empt (group) priority**, which decides whether one interrupt can
  interrupt another, and **sub-priority**, which only breaks ties among
  simultaneously-pending interrupts of the same group. Same-group interrupts
  **cannot** pre-empt each other regardless of sub-priority. That distinction is
  genuinely discriminating.
  Q2's reasoning is also worth having: **minimum inter-arrival time is a good
  proxy for priority**, but not the only factor — criticality matters (their
  emergency-stop example: interrupts once in years, still highest priority) and
  so does handler length.
- **Q4/Q5 — pending vs active, thread vs handler mode.** Know that an interrupt
  can be *pending* (requested, not yet serviced) and *active* (being serviced)
  simultaneously, and that the core runs in **Thread mode** for normal code and
  **Handler mode** inside an exception.
- **Q7 + the NVIC quiz questions** — `NVIC_SetPriority` writes IPR (external
  interrupts) or SHPR (system exceptions); `NVIC_SetPriorityGrouping` writes the
  PRIGROUP field of AIRCR. And know **PRIMASK / FAULTMASK / BASEPRI** as the
  three ways to mask interrupts — that's your answer to *"how do you implement a
  critical section on a Cortex-M?"*

**Do NOT memorise** the eight priority-group bit-split encodings (which bit is
pre-empt vs sub for group 3 vs 6 vs 7). That is EE2028 exam minutiae with zero
interview value. Concept yes, encoding table no.

---

## 🔴 Tier 1 — Tutorial 3: GPIO · **35 minutes**

Short, and it is pure register programming — exactly the JD's world.

**Q1** is the read-modify-write idiom: read the register, `BIC` to clear the
target bits, `ORR` to set the new value, write back — *without disturbing the
other pins*. The C equivalent is the `SET_BIT`/`CLEAR_BIT` macros already in your
`02_embedded_c.c`. If they ask "configure pin 14 without affecting the rest,"
this is the answer.

**Q2** is memory-mapped register access from C:
`unsigned int* GPIOA_IDR = (unsigned int*) 0x48000010;`

**Two things to extract, and the second is the good one:**

1. **BSRR and BRR are the point.** These are set/reset registers where writing a
   1 sets or clears the corresponding pin and writing a 0 does nothing — so a
   single store changes one pin **with no read-modify-write at all**. That means
   no race with an ISR touching another pin on the same port. If you're asked
   "how do you toggle a GPIO safely from both main and an interrupt", the answer
   is "use the atomic set/reset register, not `ODR |= …`."

2. **That code is missing `volatile`, and you should notice it.** See below.

---

## 🎯 The `volatile` observation — verified, and worth using carefully

Your notes declare the register pointers as `unsigned int*`, not
`volatile unsigned int*`. I compiled both versions at `-O2` to check what
actually happens, because this is the kind of claim you don't want to make
loosely in an interview.

**The honest result, in two parts:**

**(a) The tutorial's specific loop survives** — the compiler still re-reads
`*GPIOA_IDR` on each iteration. Not because the code is correct, but because the
stores to `*GPIOB_BRR` and `*GPIOB_BSRR` *might* alias the same memory, and the
compiler can't prove they don't, so it's forced to reload. **It works by
accident.** Remove those stores, or let the compiler prove no aliasing, and it
breaks.

**(b) The classic form does break, provably.** `while (!flag) { }` where `flag`
is a plain global set by an ISR compiles at `-O2` to:

```
	movl	flag_plain(%rip), %eax     ; load ONCE, before the loop
	testl	%eax, %eax
	jne	.L1
.L3:
	jmp	.L3                        ; <-- unconditional infinite loop
```

The load is hoisted clean out of the loop. Add `volatile` and the load moves back
inside, where it belongs. `04_volatile_demo.c` reproduces this — run it yourself
so you've *seen* it rather than been told it.

**How to use this on Friday.** Not as "my lecturer was wrong" — it's a teaching
simplification and saying that reads badly. Use it as your answer when `volatile`
comes up:

> *"My course notes wrote memory-mapped registers as plain `unsigned int*`. That
> particular loop happens to still work, because the compiler can't prove the
> stores don't alias the load, so it reloads anyway. But it's working by
> accident. The moment you write the same pattern as `while (!flag)` with an
> ISR-set flag, GCC at -O2 hoists the load and you get an unconditional infinite
> loop. I've compiled it and looked at the assembly. That's why `volatile` on
> MMIO and ISR-shared state isn't a style preference."*

That answer does three things at once: shows you read code critically, shows you
read *disassembly* (which ties straight to your thesis's GCC optimisation-flag
work), and shows you distinguish "works" from "correct." Very few candidates can
draw that distinction.

---

## 🟡 Tier 2 — Tutorial 6: UART · **30 minutes, four questions only**

- **Q2 — why START and STOP are opposite logic levels.** Beautiful
  first-principles answer: UART is asynchronous with no shared clock, so the
  receiver recovers timing from the **high-to-low edge at the start bit**. If
  STOP were the same level as START, back-to-back characters wouldn't guarantee
  an edge. This is a very commonly asked question and the reasoning is the whole
  answer.
- **Q3 — baud vs throughput.** A frame is 1 start + 8 data + 0 parity + 1 stop =
  **10 bits**, so 10,000 baud → 1,000 characters/second. The point is that
  **baud rate is not data rate** — framing overhead is 20% here.
- **Q4 — sending a 32-bit int over a byte channel.** This is *literally*
  `store_be32` / `load_be32` from your `02_embedded_c.c`. The notes give both
  methods and flag the trap: the pointer-cast version is faster but **only works
  if both ends share endianness**; the shift-and-or version is portable. Your
  file's rule — **"never cast, always shift"** — is the same conclusion. Nice
  convergence: your course notes and your interview prep independently agree.
- **Q7 — TXE vs TC.** TXE = the data register is free, you can write the next
  byte (the shift register may still be transmitting). TC = the shift register
  has fully drained. Waiting on TC when you only needed TXE costs you throughput.
  This is the double-buffering question.

**Skip** Q5 (XON/XOFF flow control) and Q6 (error flags) unless you have slack —
both are marked self-study / not examinable and are lower yield.

---

## 🟡 Tier 2 — Tutorial 4: I2C · **20 minutes, mostly one question**

**Q5 is the best engineering-judgement item in the whole pack**, and it rhymes
directly with your thesis. The `HTS221_T_ReadTemp()` function re-reads the
sensor's calibration registers on every single call. The calibration constants
are **fixed for a given chip** — so read them once at init and cache them.
Transaction size drops from **21 bytes to 5** per call.

The notes then state the general lesson explicitly: *"most library functions are
written to favour ease of use / flexibility, but compromise on efficiency /
power… hence the importance of being able to tweak driver functions on your
own."*

That is a Thales sentence. It is also your thesis in miniature: you didn't accept
LZ4 and heatshrink as given, you profiled them and built something that fit the
constraint. **Have this example ready** — if they ask "tell me about a time you
optimised something," you now have two: your thesis at the algorithm level and
this at the driver level.

**Also worth 5 minutes:** Q1/Q2 — which bus suits which job, and **bit-banging**
(implementing a protocol in software on plain GPIO pins when no hardware
peripheral is available). Knowing the term is worth it.

**Skip entirely:** counting exact START/ACK/NACK/byte totals for HTS221 register
sequences (Q3), the `| 0x80` autoincrement detail (Q4), the SDA/SCL pulse
drawings (Q7), and the I2C_ISR bit walkthrough (Q8). Pure exam minutiae.

---

## ⚪ Tier 3 — Skip before Friday

| Section | Why skip |
|---|---|
| **Tutorial 1** — Microprocessor Concepts | Fetch-decode-execute, RISC load/store, two's complement, NZCV flags. You know this. Only Q5 (two's complement + flag setting) has mild value, and it's 60 seconds. |
| **Tutorial 2** — ARMv7E-M Assembly | **Near-zero value.** Thales wants C. You need to *read* disassembly (you already can — you did GCC optimisation-flag analysis on your thesis), not hand-write ARM assembly. Nobody will ask you to write an assembly Fibonacci loop. |
| Quiz 2 / Quiz 3 MCQs | HAL vs CMSIS vs BSP library organisation, specific STM32 register addresses, board connector pinouts. Board-specific trivia. |

**Two single-line exceptions worth lifting from the quizzes:**

- **ADC resolution = full-scale range ÷ (2ⁿ − 1).** The altimeter question:
  200 m range ÷ (2¹⁰ − 1) = **0.195 m/LSB**. One formula, occasionally asked.
- **The library stack**: **CMSIS** (ARM's core/register abstraction) → **HAL**
  (ST's peripheral drivers) → **BSP** (board-specific support). Knowing the
  layering in one sentence is enough; don't memorise which header holds what.

---

## Thursday morning, revised

| Time | What |
|---|---|
| 09:00–10:30 | **Tutorial 5** end to end + PLAYBOOK §3 interrupts. Write the 6 ISR rules from memory. Add **WCET** and **PRIMASK/BASEPRI** to your vocabulary. |
| 10:45–11:20 | **Tutorial 3** + run `04_volatile_demo.c` and read the assembly yourself |
| 11:20–11:50 | **Tutorial 6** Q2, Q3, Q4, Q7 + **Tutorial 4** Q5 |
| 11:50–12:00 | Draw the UART/SPI/I²C table from memory |

Everything else in the pack: after Friday, if ever.
