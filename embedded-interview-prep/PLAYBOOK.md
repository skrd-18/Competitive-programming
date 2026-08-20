# Thales ECC — Software Engineer (Embedded Systems)
## Interview Playbook — Friday 21 Aug 2026, 10:00

---

## 0. The one finding that should reshape your prep

Candidate reports of Thales technical assessments describe questions like
**"print a pyramid using a char array"** and **"remove duplicates from an array
and print the result"**, with marking weighted on *exact output formatting*.
The stated hiring philosophy is that Thales favours candidates who
**"can explain their own work with precision"** over polished performance.

Read that twice, because it means:

- **Do not spend Wednesday grinding hard dynamic programming.** That is not what
  gets asked, and every hour there is an hour stolen from what does.
- **Flawless fundamentals beat clever algorithms.** Correct output, correct edge
  cases, correct memory handling, said out loud.
- **Your thesis is the highest-leverage thing you own.** "Explain your own work
  with precision" is a description of a resume deep-dive, and yours has a hard
  number in it — 3.11 µA — that a good interviewer will absolutely drill.

So the plan weights: **40% C fundamentals + sorting, 25% thesis deep-dive
rehearsal, 20% embedded/EE2028 recall, 15% domain and behavioural.**

---

## 1. Honest read of your position

### What is genuinely strong

| Asset | Why it matters here |
|---|---|
| B.Eng. EE, Honours **(Distinction)**, GPA 4.24/5.00 | Above the bar; Distinction is top-tier |
| **EE2028 grade: A** | Microcontroller Programming & Interfacing — the single most JD-relevant module on the transcript |
| **EE4002D Capstone: A** (8 units) | Your embedded thesis, top grade, heavyweight module |
| Thesis: C on ARM Cortex-M4 (nRF52840), lossless compression, 3.11 µA | Real embedded engineering with a measured result. This is your centrepiece. |
| Ported/benchmarked 8 embedded C libraries (LZ4, heatshrink, uzlib, PackBits) | Proves you can read and port other people's C on constrained targets |
| DWT cycle counting, PPK2 current profiling, SEGGER RTT, GDB | Genuine debug-and-measure toolchain fluency — the JD explicitly asks for "proven problem-solving and debugging skills" |
| Poly diploma with Merit + Director's Honour Roll ×2 | Consistent record, plus hands-on EEE foundation |

### What is genuinely a gap — and what to do about each

| Gap | Reality | Move |
|---|---|---|
| **"Minimum 3 years relevant experience"** | You graduated Jun 2024. ~2 years professional, and the EMA role was Python/data, not embedded. | Reframe: count the thesis (Aug 2023–Apr 2024) as embedded engineering, because it was. See §7. |
| **EMA role is not embedded** | Python, Docker, Linux, solar forecasting. | Bridge it: optimisation, profiling, and measurement discipline are the *same* skill applied to a different target. See §7. |
| **You have exited EMA** | Your resume still says "Aug 2024 – Present". | **Fix this before Friday.** See §8 — this is urgent and easy. |
| **CS2040C shows W on the transcript** | Withdrawn in AY2023/24 Sem 2. They may have the transcript. | Turn it into your best answer. See §7. It is a strength if you frame it right. |
| **Java is thin** | Resume says "Java (OOP)". JD says "Proficient in C/Java", and names **Javacard** as a plus. | You will not become a Java expert by Friday. Get to honest competence + domain awareness. See §5. |

### The thing nobody will tell you

Your transcript shows several **W**s in your final year — CS2040C, EE4802,
EE3305, CFG1002, CFG3001 — alongside an **A in the 8-unit capstone**. That is a
recognisable pattern: you shed load to protect the thing that mattered. If asked,
say exactly that. It is a defensible engineering trade-off — prioritisation under
a resource constraint — and it is a far better answer than an apology.

---

## 2. Who you are actually interviewing with

Thales Singapore **Engineering Competence Centre (ECC)** is the Digital Identity
& Security arm — this is the **ex-Gemalto** business. That single fact explains
the whole JD.

What they build: **SIM / eSIM / eUICC / iSIM**, **embedded secure elements
(eSE)**, banking and payment cards, government eID, IoT connectivity modules.

Now re-read the JD's phrases with that lens:

- *"advance software security mechanism"* → side-channel and fault-attack countermeasures on a secure element
- *"next generation IoT connectivity protocols"* → eSIM / remote SIM provisioning, LPWAN
- *"next generation operating systems for future devices"* → the **card OS** that runs on a secure element — a real, tiny, hardened OS
- *"Proficient in C/Java"* → C for the card OS itself; **Java for Java Card applets** running on top of it
- *"Javacard knowledge is a plus"* → the actual technology

**If you walk in knowing what Java Card is, you will be in a small minority of
candidates.** This is the cheapest differentiation available to you. §4 is the
crash course.

---

## 3. Embedded / EE2028 recall sheet

You got an A in this. It is in there — this is retrieval, not learning.

### ARM Cortex-M architecture

- **Registers**: R0–R12 general purpose; **R13 = SP** (banked: MSP for
  handler/main, PSP for threads), **R14 = LR** (return address), **R15 = PC**.
  **xPSR** = APSR (flags) + IPSR (current exception number) + EPSR (Thumb bit).
- **Thumb-2**: mixed 16/32-bit instruction encoding — density of 16-bit with the
  power of 32-bit. Cortex-M executes **Thumb only**; the T-bit must stay set or
  you take a UsageFault.
- **M0/M0+**: ARMv6-M, no DSP, no FPU, 2-stage pipeline. **M4**: ARMv7-M, DSP
  extensions (SIMD, MAC), optional FPU. **M4F** = M4 with FPU. Your nRF52840 is
  an **M4F**.
- **Memory map** is architecturally fixed: Code 0x0000_0000, SRAM 0x2000_0000,
  Peripheral 0x4000_0000, Private Peripheral Bus 0xE000_0000 (where NVIC,
  SysTick and **DWT** live — the DWT is the cycle counter you used).
- **Bit-banding** (M3/M4): aliases a whole region so a single bit can be
  read/written atomically with one normal load/store — no read-modify-write race.

### Interrupts — the topic most likely to be probed

- **Vector table** at the start of flash. **First word is the initial stack
  pointer**, second is the reset vector. This detail impresses people.
- **NVIC**: nested, prioritised. **Lower priority number = higher urgency.**
  Priority splits into pre-empt and sub-priority fields.
- **Exception entry**: hardware automatically stacks **R0–R3, R12, LR, PC,
  xPSR** (8 words). Because the AAPCS caller-saved set is pushed for you, an ISR
  can be a plain C function — no `__interrupt` wrapper needed.
- **EXC_RETURN**: the magic value loaded into LR on entry (0xFFFFFFFx); its low
  bits encode which stack to unwind and whether FP state was pushed.
- **Tail-chaining**: back-to-back interrupts skip the unstack/restack, saving
  ~12 cycles. **Late arrival**: a higher-priority IRQ arriving during stacking
  pre-empts without redoing the push.

**ISR rules — say these as a list, it lands well:**
1. Keep it short. Set a flag or push to a queue; do the work in main.
2. **No `malloc`, no blocking, no `printf`** inside an ISR.
3. Shared variables must be **`volatile`**.
4. `volatile` is **not** atomicity — a read-modify-write still needs a critical
   section or an atomic.
5. **Clear the interrupt flag**, or you re-enter immediately.
6. Watch stack depth: nested ISRs stack on the same stack.

### Peripherals

| Bus | Wires | Speed | Duplex | Use |
|---|---|---|---|---|
| **UART** | 2 (TX/RX), async | Low | Full | Debug console, GPS, modems |
| **SPI** | 4 (MOSI/MISO/SCK/CS) | High (10s of MHz) | Full | Flash, displays, radios |
| **I²C** | 2 (SDA/SCL), addressed | Moderate | Half | Sensors, EEPROM, many devices on one bus |

- **UART has no clock line** — both ends must agree on baud rate; mismatch
  produces framing errors. That's the classic "why is my serial garbage" answer.
- **I²C** is open-drain and needs pull-ups; supports multiple masters and
  addresses devices on the bus.
- **SPI** is faster but needs a chip-select per device.
- **ADC**: resolution (12-bit on your part), sampling rate, **Nyquist** (sample
  above 2× the highest frequency), aliasing, reference voltage.
- **Polling vs interrupt vs DMA**: polling wastes CPU and cannot sleep;
  interrupt is event-driven; **DMA** moves bulk data with zero CPU involvement,
  which is what lets the core stay asleep — directly relevant to your thesis.

### Startup, memory, and the linker

- **`.text`** = code + constants (flash). **`.data`** = initialised globals
  (lives in flash, **copied to RAM at startup**). **`.bss`** = zero-initialised
  globals (**zeroed at startup**, occupies no flash). **heap** grows up,
  **stack** grows down (full descending on ARM).
- Startup sequence: SP loaded from vector table → Reset_Handler → copy `.data`
  from flash to RAM → zero `.bss` → call `SystemInit` → `main`.
- A **linker script** defines the memory regions and section placement. Reading
  the `.map` file to find what is eating your flash is a real skill — mention it.
- **Stack overflow** on an MCU is silent by default: it walks into `.bss`.
  Mitigations: MPU guard region, stack painting/watermarking, `-fstack-usage`.

### Low power (your home turf)

Sleep modes trade wake latency against current: run → sleep (core clock off,
peripherals live) → deep sleep / stop (most clocks off, RAM retained) → standby
(RAM lost, near-zero current). The engineering is: **stay in the deepest mode
for the highest duty-cycle fraction**, wake on interrupt or DMA completion, and
never poll. You did exactly this — say it in these terms.

### Debugging

- **JTAG vs SWD**: SWD is 2-wire (SWDIO/SWCLK) versus JTAG's 4–5. Same debug
  access, far fewer pins — which is why it wins on small packages.
- **SEGGER RTT**: reads/writes a RAM buffer over the debug probe, so it gives
  you `printf`-style tracing with almost none of the timing distortion a UART
  `printf` causes. Saying *why* RTT beats UART printf is a good answer.
- **DWT cycle counter**: `CYCCNT` for exact cycle-accurate timing.
- **Hard fault debugging**: read the fault status registers (CFSR, HFSR),
  recover the stacked PC to find the faulting instruction. Common causes:
  unaligned access, null/wild pointer, stack overflow, executing non-Thumb.
- **Heisenbug**: a bug that vanishes under the debugger — usually a timing or
  race issue, or a `volatile` you forgot.

---

## 4. Java Card & secure elements — the differentiator

Spend 45 minutes here. It converts directly into interview signal.

### What Java Card is

A **subset of Java that runs on a smart card / secure element** with only a few
KB of RAM. Applications are **applets**; the runtime is the **JCRE** (Java Card
Runtime Environment) over the **JCVM**.

**What it removes versus standard Java** — this is the interesting part, and it
is all embedded reasoning:

- No garbage collector on classic cards (or a very limited one) — you allocate
  objects **once, at install time**, and reuse them forever. Allocating in a
  transaction loop leaks card memory permanently.
- No threads, no dynamic class loading, no reflection.
- No `float`/`double`; `int` is optional. You work in `byte` and `short`.
- No `String`; you work with byte arrays.

**Memory model** — the concept most worth knowing:
- **Persistent memory (EEPROM/flash)**: fields survive power loss. Writes are
  **slow** and have **limited endurance**.
- **Transient memory (RAM)**: `JCSystem.makeTransientByteArray(...)`, cleared on
  reset or on deselect. Use it for scratch — session keys, working buffers.
- **Transactions**: `JCSystem.beginTransaction()` / `commitTransaction()` give
  **atomicity across power loss**. If the card is yanked mid-update, the state
  rolls back. This is the whole reason card OSes are hard, and it is a fantastic
  thing to bring up unprompted.

### APDU — the protocol

All card communication is **command/response APDUs** (ISO 7816-4):

```
Command:   CLA  INS  P1  P2  [Lc  data...]  [Le]
Response:  [data...]  SW1  SW2
```

- **CLA** class, **INS** instruction, **P1/P2** parameters, **Lc** length of
  incoming data, **Le** expected response length.
- **Status words**: `0x9000` = success. `0x6A82` = file/applet not found.
  `0x6982` = security status not satisfied. `0x6700` = wrong length.
- An applet's lifecycle: `install()` → `select()` → `process(APDU)` for each
  command → `deselect()`.

**If you remember one thing: `9000` means OK.** Dropping that casually is a
strong domain signal.

### Surrounding vocabulary

- **GlobalPlatform**: the standard for card content management — loading,
  installing and deleting applets after issuance. **Secure Channel Protocol
  (SCP02/SCP03)** gives an authenticated, encrypted channel to the card.
  **ISD** = Issuer Security Domain, the privileged on-card authority.
- **Secure element (SE)**: tamper-resistant chip with its own CPU and secure
  storage. **eSE** = embedded (soldered). **eUICC / eSIM** = a SIM whose
  operator profile can be provisioned over the air. **iSIM** = integrated into
  the main SoC die.
- **Root of trust / secure boot**: each stage cryptographically verifies the
  next before executing it — a chain from immutable ROM upward.
- **Side-channel attacks**: **SPA/DPA** (reading secrets from power consumption),
  **timing attacks**, **EM analysis**. Countermeasures: **constant-time code**
  (no secret-dependent branches or memory indices), **masking/blinding**,
  random delays, balanced logic.
- **Fault injection**: glitching voltage, clock or laser to skip an instruction —
  typically to bypass a PIN check. Countermeasures: **double-checking critical
  branches**, redundant computation, integrity checks on sensitive flags.
- **Common Criteria / EAL**: the formal security certification scheme these
  products are evaluated under. EAL5+/6+ is typical for secure elements.

### Constant-time comparison — write this one out, it is the perfect answer

```c
/* WRONG: returns early, so execution time leaks how many bytes matched.
 * An attacker times the response and recovers the secret byte by byte. */
bool bad_compare(const uint8_t *a, const uint8_t *b, size_t n) {
    for (size_t i = 0; i < n; i++)
        if (a[i] != b[i]) return false;      /* <-- the leak */
    return true;
}

/* RIGHT: always touches all n bytes, no secret-dependent branch. */
bool ct_compare(const uint8_t *a, const uint8_t *b, size_t n) {
    uint8_t diff = 0;
    for (size_t i = 0; i < n; i++)
        diff |= (uint8_t)(a[i] ^ b[i]);       /* accumulate, never branch */
    return diff == 0;
}
```

If any question touches security and C, steer to this. It is short, it is
correct, and it demonstrates exactly the mindset the "advance software security
mechanism" line in the JD is asking for.

---

## 5. Java — get to honest competence

You will not be a Java expert by Friday. Aim to answer confidently and not
overclaim. If they push past your depth: *"I've used Java for OOP work and I'm
comfortable with the language model; I haven't shipped a large Java codebase.
Given C is my primary language, I'd expect to be productive in Java quickly —
and I've been reading up on Java Card specifically because of this role."*
That is a strong answer. Overclaiming and then failing a follow-up is fatal.

**Know cold:**

- **JVM / bytecode / JIT**: source → bytecode → JVM interprets and JIT-compiles
  hot paths. "Write once, run anywhere."
- **Four pillars**: encapsulation, inheritance, polymorphism, abstraction.
- **Overloading** (same name, different parameters, compile-time) vs
  **overriding** (subclass replaces a superclass method, runtime dispatch).
- **`interface` vs `abstract class`**: a class implements many interfaces but
  extends one class; abstract classes can hold state and constructors.
- **`final`**: variable = cannot be reassigned; method = cannot be overridden;
  class = cannot be extended.
- **Checked vs unchecked exceptions**: checked must be declared or caught.
- **`==` vs `.equals()`**: reference identity vs value equality. The classic
  String-interning trap.
- **Pass-by-value always** — but for objects the *value passed is the reference*.
  Say it that precisely.
- **GC**: generational, mark-and-sweep. **And then pivot**: *"which is exactly
  what Java Card removes, because you can't afford a collector on a card — so
  applets allocate once at install time and reuse."* That pivot is the whole
  point of learning this section.

**C vs Java, when asked** (near-certain given "Proficient in C/Java"):
manual memory vs GC; pointers vs references; compiled-to-native vs
bytecode-on-a-VM; deterministic timing vs GC pauses (which is precisely why
hard-real-time and secure-element code is written in C).

---

## 6. Complexity table — be able to draw this from memory in 60 seconds

| Algorithm | Best | Average | Worst | Space | Stable | Use it when |
|---|---|---|---|---|---|---|
| Insertion | O(n) | O(n²) | O(n²) | O(1) | ✅ | n small (<16), or nearly sorted |
| Selection | O(n²) | O(n²) | O(n²) | O(1) | ❌ | writes are expensive (EEPROM/flash) |
| Bubble | O(n) | O(n²) | O(n²) | O(1) | ✅ | never (teaching only) |
| **Merge** | O(n log n) | O(n log n) | O(n log n) | **O(n)** | ✅ | need stability + guaranteed bound |
| **Quick** | O(n log n) | O(n log n) | **O(n²)** | O(log n) | ❌ | general purpose, best cache behaviour |
| **Heap** | O(n log n) | O(n log n) | O(n log n) | **O(1)** | ❌ | **need a hard worst case AND no extra RAM** |
| Counting | O(n+k) | O(n+k) | O(n+k) | O(k) | ✅ | small known integer range |
| Radix | O(d·n) | O(d·n) | O(d·n) | O(n+k) | ✅ | fixed-width integer keys |

**The embedded answer they're fishing for:** for a memory-constrained target
needing a guaranteed bound, **heapsort** — O(n log n) worst case *and* O(1)
space. Quicksort is usually faster but its O(n²) worst case is unacceptable when
you must certify a bound.

**Why O(n log n) is the comparison-sort floor**: n! possible orderings, each
comparison gives one bit, so you need log₂(n!) ≈ n log n comparisons. Counting
and radix beat it only because they never compare — they index.

Also know: **O(1) < O(log n) < O(n) < O(n log n) < O(n²) < O(2ⁿ) < O(n!)**, and
that **amortised** O(1) (dynamic array push) means averaged over a sequence, not
guaranteed per operation.

---

## 7. Story framing — rehearse these out loud

> Write nothing here as a script to recite. Rehearse until you own the *shape*
> of each answer, then speak it fresh.

### 7.1 The thesis deep-dive — your centrepiece

They will drill this, and "explain your own work with precision" is reportedly
what they select on. Be ready for **at least four layers deep**:

1. *What did you build?* — a lossless compression algorithm in C for ECG data on
   an nRF52840 (Cortex-M4F) wearable.
2. *Why compress at all?* — the radio dominates the energy budget. Fewer bytes
   transmitted beats faster computation, so compression trades a little CPU for
   a lot of radio-off time.
3. *Why write a new one instead of using LZ4/heatshrink?* — you **ported and
   benchmarked eight** first. The existing ones needed dictionary tables and had
   variable memory footprints; you needed a **fixed** footprint sized for the SoC
   and predictable behaviour.
4. *How did you get 3.11 µA, and how do you know?* — **this is the question.**
   Be precise: measured with a Nordic PPK2, averaged over what window, at what
   duty cycle, against what baseline, on what data set. If you are unsure of a
   number, say what you measured and how, rather than guessing.
5. *What was the compression-vs-power trade-off curve?* — you said you tuned
   each algorithm to map it. Be able to describe the shape and where the knee was.
6. *What would you do differently?* — always have an answer. Perhaps: a larger
   or more diverse ECG dataset, or testing against motion-artifact-heavy data, or
   formalising worst-case bounds on the compression ratio.

**Prepare for the hostile version**: *"3.11 µA sounds low. What exactly is
included in that figure?"* Do not get defensive. Answer with the measurement
setup. Confidence about method beats confidence about the number.

### 7.2 "You have under 3 years of embedded experience"

Do not apologise, do not pretend. Reframe the denominator.

> *"If you count from graduation, that's right — about two years. But my
> embedded work started with my thesis in August 2023: eight months of daily C
> on a Cortex-M4, porting and benchmarking eight compression libraries on target
> and profiling them with a PPK2 and the DWT cycle counter. That was full-time
> embedded engineering, and it's the work I'd point to. What I'd add is that the
> gap you're describing is in years, not in the skills — I'm fluent in the
> toolchain, I've debugged on hardware, and I've shipped a measured result. I'd
> rather be judged on what I can do on a whiteboard on Friday than on a date."*

Then **stop talking**. Do not fill the silence.

### 7.3 "Why did you leave EMA?" — you must have this ready

You have exited, so this is coming. Keep it short, forward-looking, and never
negative about EMA.

> *"The work was real — I cut a national solar-forecasting simulation's runtime
> by 30% and built the pipeline behind the reference method for quantifying
> forecast drift. But it was Python and data engineering, and the thing I
> actually want to do is low-level C on constrained hardware. My thesis is the
> work I'm proudest of, and I decided I'd rather commit fully to getting back to
> that than drift further from it. That's why this role specifically."*

If pressed on the timing/gap: be straightforward about the date, note you've
been using the time to close the DSA gap (§7.4) — which is *true and verifiable*
and turns the gap into evidence of initiative.

### 7.4 "Your transcript shows you withdrew from CS2040C"

**This is your best answer of the day if you frame it right.** Do not hide from
it — they may well have the transcript in front of them.

> *"In my final semester I was carrying the 8-unit capstone, and I made a call
> to drop load and protect it. I got an A on the capstone and the thesis became
> the strongest work I've done, so I stand by the trade-off — but the cost was a
> real gap in formal data structures. I'm not comfortable leaving a gap I know
> about, so I'm working through CS2040C now. I'm on sorting this week — I
> implemented the full set in C rather than C++, including the embedded-specific
> reasoning about when heapsort's O(1) space beats quicksort's speed."*

Why this works: it shows prioritisation under constraint, self-awareness,
follow-through, and **it is happening right now**, which no other candidate can
claim. You are turning your weakest line into a demonstration of exactly the
"proactive" trait the JD asks for.

### 7.5 The EMA → embedded bridge

Do not let the EMA role read as irrelevant. It is the same discipline:

> *"Restructuring that parallel hindcast to cut runtime 30% was profiling work —
> find the hot path, understand why it's hot, restructure it, measure again.
> That's the identical loop I ran on the Cortex-M4 with the DWT cycle counter
> and GCC optimisation flags. The target changed; the method didn't. And the
> pyranometer pipeline was fundamentally about trusting your measurement before
> trusting your conclusion, which is the habit that made the 3.11 µA figure
> defensible."*

### 7.6 "Why Thales?"

Be specific. Generic answers are transparent.

> *"Two reasons. First, the domain: ECC is the digital identity and security
> side — secure elements, eSIM, card operating systems. That's C running under
> genuinely hard constraints, where memory, power and timing all matter and are
> also security properties. Constant-time code isn't a style preference there,
> it's a countermeasure. That's a level of rigour I want to work at. Second, my
> thesis was fundamentally about making an algorithm provably efficient on
> constrained hardware, and the JD's line about developing next-generation
> embedded operating systems is the same problem with higher stakes."*

### 7.7 Standard behavioural — prepare one story each (STAR)

| Question | Your material |
|---|---|
| Hardest technical problem | Isolating the performance bottleneck via DWT + optimisation-flag analysis |
| Disagreement with a colleague/supervisor | Your algorithm choice vs an existing library — argue it on measured data |
| A failure / mistake | The eight-library benchmarking — something surely didn't port cleanly first time |
| Working under pressure | Final year: capstone + the decision to drop modules |
| Teamwork | Capstone team, Orbital (CP2106), EMA cross-team work |
| Learning something fast | Porting eight unfamiliar C codebases onto a target |

The JD explicitly says **"team player… ability to work independently and being
proactive."** Make sure at least two stories show *proactive* — you saw
something and acted without being told.

---

## 8. Do these three things before Friday

1. **Fix your resume.** It says "Energy Market Authority — Aug 2024 – **Present**"
   and that is no longer true. Change it to an end date. If the interviewer
   notices the discrepancy before you mention it, you have a credibility problem
   that is entirely avoidable. Bring 2–3 clean printed copies.
2. **Re-read your own thesis.** Especially the measurement methodology and the
   results table. You wrote it 16+ months ago. The one thing that would really
   hurt is fumbling a number from your own paper.
3. **Check your setup Thursday night** — the shared editor, camera, mic,
   internet, and a quiet room. For a live-coding round, also decide where your
   hands and notes go, and have a physical notepad and pen for drawing.

---

## 9. Live-coding protocol — the part most candidates get wrong

The code is maybe half the assessment. The other half is whether they'd enjoy
debugging something with you at 6pm on a Thursday.

**Before writing a line:**
1. **Restate the problem** in your own words. Confirm you have it right.
2. **Ask about constraints**: input size, value range, sorted or not, duplicates
   allowed, can I modify the input in place, memory limits.
3. **State your assumptions out loud** and check them. *"I'll assume the array
   fits in memory and I can modify it in place — tell me if not."*
4. **Say the approach and its complexity before coding.** *"I'll do two
   pointers, O(n) time, O(1) space."* If they were hoping for something else,
   this is where they redirect you — cheaply.

**While writing:**
5. **Narrate.** Silence is the enemy. *"I'm starting j at i-1 because…"*
6. **Handle edge cases explicitly**: NULL, n=0, n=1, all-equal, already sorted,
   reverse sorted, overflow. Even a comment `/* n==0 handled by the loop guard */`
   earns the point.
7. **Check every `malloc`.** In an embedded interview this is not pedantry, and
   they *will* notice if you skip it.
8. **Use `lo + (hi - lo) / 2`**, never `(lo + hi) / 2`, and say why.

**After:**
9. **Trace through a small example by hand**, out loud, before declaring done.
   Find your own bug — that's the strongest possible signal.
10. **Volunteer the weakness.** *"This is O(n²); if n were large I'd sort first
    and use two pointers, or use a hash set at O(n) space."*

**When stuck:** say what you're thinking, state what you know, propose the brute
force and then optimise. Never go silent. *"Let me start with the obvious
O(n²) and then look for the redundant work"* is always a valid opening.

**Never** say "this is easy." **Never** guess silently and hope. **Never** argue
when corrected — say *"you're right, let me fix that"* and fix it.

---

## 10. Questions to ask them

Have 5 ready; you'll get to ask 2–3. Avoid anything answerable from the website.

1. *"Is the embedded product team working closer to the card OS itself, or the
   Java Card applet layer on top? Where would this role sit?"*
2. *"What does the validation side look like — how much is on-target testing
   versus simulation, and what does the test infrastructure look like?"*
3. *"The JD mentions next-generation OSes for future devices. Is that
   iSIM-directed, or a broader secure-element platform effort?"*
4. *"How is security review integrated into the development cycle — is there a
   dedicated evaluation team, or does it sit with the developers?"*
5. *"You mention working with teams around the world — what does a typical
   sprint look like across those time zones?"*
6. *"What would you want someone in this role to have accomplished by the end of
   their first six months?"*

**Do not** ask about salary, leave, or WFH in a technical round.

---

## 11. Friday morning, 08:00–09:45

Do **not** learn anything new. Nothing new goes in after Thursday night.

- 08:00 — Re-read §6 (complexity table) and §7.1 (thesis). Nothing else.
- 08:30 — Write `insertion_sort` and `list_reverse` from memory, once each. Just
  to prove to yourself the hands still work.
- 09:00 — Read your one-page cheat sheet. Eat something.
- 09:30 — Setup check. Water within reach. Notepad and pen out.
- 09:50 — Close every tab. Two minutes of silence.

You are not walking in as an underqualified candidate. You are an
Honours-with-Distinction engineer with an A in microcontroller programming, an A
on an embedded capstone, and a measured 3.11 µA result you can defend in depth.
Go and explain your own work with precision.

---

### Sources

- [Thales Software Engineer Interview Guide — InterviewQuery](https://www.interviewquery.com/interview-guides/thales-software-engineer)
- [Thales Embedded Software Engineer interviews — Glassdoor](https://www.glassdoor.com/Interview/Thales-Embedded-Software-Engineer-Interview-Questions-EI_IE10358.0,6_KO7,33.htm)
- [Thales interviews — NodeFlair (Singapore)](https://nodeflair.com/companies/thales/interviews)
- [Thales — Secure SIM and eSIM solutions for mobile connectivity](https://www.thalesgroup.com/en/markets/digital-identity-and-security/technology/javacard)
- [Thales — Embedded Secure Element (eSE) Solutions](https://www.thalesgroup.com/en/solutions-catalogue/enterprise/mobile-communications/embedded-secure-element-ese-solutions)
- [ThalesGroup/libse-gto — Secure Element APDU T=1 over SPI](https://github.com/gemalto/libse-gto)
- [NUSMods — EE2028 Microcontroller Programming and Interfacing](https://nusmods.com/courses/EE2028/microcontroller-programming-and-interfacing)
