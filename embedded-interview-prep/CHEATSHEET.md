# One-Page Cheat Sheet — Fri 21 Aug, 10:00

> Handwrite your own version Thursday night. The writing *is* the revision.
> Use this only to check yourself against afterwards.

## Complexity

| | Best | Avg | Worst | Space | Stable |
|---|---|---|---|---|---|
| Insertion | n | n² | n² | 1 | ✅ |
| Selection | n² | n² | n² | 1 | ❌ |
| Merge | n log n | n log n | n log n | **n** | ✅ |
| Quick | n log n | n log n | **n²** | log n | ❌ |
| Heap | n log n | n log n | n log n | **1** | ❌ |
| Counting | n+k | n+k | n+k | k | ✅ |
| Radix | d·n | d·n | d·n | n+k | ✅ |

- **Memory-constrained + hard worst-case bound → heapsort.** Only one that is both O(n log n) worst *and* O(1) space.
- **Writes expensive (EEPROM/flash) → selection sort.** ≤ n−1 writes.
- **n < 16 or nearly sorted → insertion.** Smallest constant factor.
- **Lower bound**: log₂(n!) ≈ n log n. Counting/radix beat it by *indexing*, not comparing.
- `mid = lo + (hi - lo) / 2` — never `(lo + hi) / 2`. Overflow.

## C traps

- `const char *p` = pointer to const char · `char * const p` = const pointer. **Read right-to-left.**
- `volatile` = reload from memory every access. Needed for: MMIO registers, ISR-shared vars, setjmp.
- **`volatile` ≠ atomic.** Read-modify-write still needs a critical section.
- `sizeof(array)` = bytes; `sizeof(pointer)` = 8. `strlen` = chars before NUL.
- `memmove` handles overlap; `memcpy` is UB on overlap.
- Comparator: `return (x>y)-(x<y)`, **not** `x-y` (overflows at INT_MIN).
- **Never call a function and read its out-param in the same argument list** — argument evaluation order is unspecified.
- Check every `malloc`.

## Bit ops

```c
#define BIT(n)          (1UL << (n))
#define SET_BIT(r,n)    ((r) |=  BIT(n))
#define CLEAR_BIT(r,n)  ((r) &= ~BIT(n))
#define TOGGLE_BIT(r,n) ((r) ^=  BIT(n))
#define TEST_BIT(r,n)   (((r) >> (n)) & 1UL)
```
- popcount: `while (v) { v &= v-1; c++; }` — one iteration per set bit
- power of two: `v && !(v & (v-1))`

## Cortex-M

- R13 = SP (MSP/PSP), R14 = LR, R15 = PC. xPSR = APSR + IPSR + EPSR.
- **Vector table word 0 = initial SP**, word 1 = reset handler.
- Exception entry auto-stacks **8 words**: R0–R3, R12, LR, PC, xPSR → so an ISR is a plain C function.
- NVIC: **lower number = higher priority.** Tail-chaining saves the unstack/restack.
- `.text` flash · `.data` flash→RAM copy at startup · `.bss` zeroed at startup.
- Startup: SP from vector table → Reset_Handler → copy .data → zero .bss → SystemInit → main.
- **UART** 2-wire async, no clock → baud mismatch = framing errors. **SPI** 4-wire, fast, full duplex, CS per device. **I²C** 2-wire, addressed, open-drain, needs pull-ups.
- **DMA** is what lets the core stay asleep.
- SWD = 2 wires vs JTAG's 4–5. **RTT** = RAM buffer over the probe → tracing without UART's timing distortion.
- Hard fault: read CFSR/HFSR, recover stacked PC.

### ISR rules
1. Short — set a flag or enqueue, do work in main
2. No malloc, no blocking, no printf
3. Shared vars `volatile`
4. `volatile` is not atomicity
5. Clear the interrupt flag
6. Watch stack depth

## Ring buffer — why it's right
Power-of-two capacity → mask not modulo (no division on M0). One slot kept empty → full vs empty without a count. Single producer + single consumer → each index has one writer → **no lock needed**. head/tail `volatile`. Publish the index **last**.

## Java Card / secure element

- **APDU**: `CLA INS P1 P2 [Lc data] [Le]` → `[data] SW1 SW2`
- **`0x9000` = success** · `6A82` not found · `6982` security status not satisfied · `6700` wrong length
- No GC, no threads, no float → **allocate once at install, reuse forever**
- **Persistent** (EEPROM, slow, limited endurance) vs **transient** (RAM, cleared on reset)
- **Transactions** = atomicity across power loss (card yanked mid-write → rollback)
- **GlobalPlatform** = content management; **SCP02/03** = secure channel; **ISD** = issuer security domain
- eSE (soldered) · eUICC/eSIM (OTA-provisionable profile) · iSIM (on the SoC die)
- Side channel: **SPA/DPA**, timing, EM → countermeasures: **constant-time**, masking, random delay
- Fault injection: voltage/clock/laser glitch to skip an instruction → **double-check critical branches**

```c
/* constant-time compare — no secret-dependent branch */
uint8_t diff = 0;
for (size_t i = 0; i < n; i++) diff |= a[i] ^ b[i];
return diff == 0;
```

## Java one-liners
Overloading = compile time, different params. Overriding = runtime, subclass replaces. `==` reference, `.equals()` value. **Always pass-by-value — for objects the value is the reference.** Checked exceptions must be declared or caught.

## Live-coding protocol
1. Restate the problem 2. **Ask constraints** (size, range, sorted?, duplicates?, in-place?, memory?) 3. State approach **+ complexity before coding** 4. Narrate continuously 5. Edge cases out loud: NULL, n=0, n=1, all-equal, sorted, reverse, overflow 6. Trace by hand before declaring done 7. **Volunteer the weakness yourself**

Stuck? *"Let me start with the obvious O(n²) and then look for the redundant work."* Never go silent.

## My numbers
- GPA **4.24/5.00**, Honours **(Distinction)** · **EE2028: A** · **EE4002D capstone: A**
- Thesis: C on **nRF52840 / Cortex-M4F**, lossless ECG compression, **3.11 µA**, 8 libraries ported (LZ4, heatshrink, uzlib, PackBits), DWT cycle counting + **PPK2** current profiling
- EMA: **30%** simulation runtime cut on the national solar-forecasting codebase

## The three answers
- **3 years?** → "Embedded work started Aug 2023 with the thesis — eight months of daily C on a Cortex-M4. Judge me on Friday's whiteboard, not a date." *Then stop talking.*
- **Why leave EMA?** → "Real work, but Python and data. I want low-level C on constrained hardware. That's why this role specifically."
- **CS2040C W?** → "Final year I dropped load to protect the 8-unit capstone. Got an A, thesis is my best work, I stand by it — but it left a real gap, so I'm working through CS2040C now. I'm on sorting this week."
