/* =====================================================================
 * 04_volatile_demo.c  --  See the volatile bug with your own eyes.
 *
 * Run:   gcc -O2 -S -o - 04_volatile_demo.c | less
 *   or:  gcc -O2 -S -o - 04_volatile_demo.c | grep -A12 "^wait_plain:"
 *
 * Don't take this on faith. Look at the assembly. Being able to say
 * "I compiled it and read the output" is worth far more in an interview
 * than "I read that volatile is important."
 *
 * This is also a direct bridge to your thesis: GCC optimisation-flag
 * analysis is on your resume, so reading -O2 output is already your
 * territory. Say so.
 * ===================================================================== */

/* ---------------------------------------------------------------------
 * CASE 1 -- The classic. This one provably breaks.
 *
 * `flag` is set by an ISR. The compiler cannot see the ISR (it is not
 * called from anywhere in this translation unit), so as far as GCC is
 * concerned nothing in the loop modifies `flag`. It hoists the load out
 * of the loop and emits an unconditional infinite jump.
 *
 * LOOK FOR, in wait_plain:
 *      movl  flag_plain(%rip), %eax   <- loaded ONCE, before the loop
 *      ...
 *  .L3:
 *      jmp   .L3                      <- infinite loop. Your firmware hangs.
 *
 * And in wait_volatile:
 *  .L6:
 *      movl  flag_volatile(%rip), %eax  <- reloaded EVERY iteration
 *      testl %eax, %eax
 *      je    .L6
 *
 * SAY: "volatile tells the compiler this object can change outside the
 *       program's control, so it must reload it from memory on every
 *       access instead of caching it in a register. Without it, a
 *       poll-on-an-ISR-flag loop compiles to an unconditional infinite
 *       loop at -O2. I've compiled it and read the assembly."
 * ------------------------------------------------------------------- */
unsigned int          flag_plain;      /* set by an ISR -- BUG */
volatile unsigned int flag_volatile;   /* set by an ISR -- correct */

void wait_plain(void)    { while (!flag_plain)    { } }
void wait_volatile(void) { while (!flag_volatile) { } }


/* ---------------------------------------------------------------------
 * CASE 2 -- Your EE2028 Tutorial 3 Q2, exactly as written in the notes.
 *
 * The notes declare these as plain `unsigned int*`, not volatile.
 *
 * THE SUBTLE PART, and the part worth saying out loud: this particular
 * loop still works. Not because it is correct, but because the compiler
 * cannot prove that the stores through GPIOB_BRR / GPIOB_BSRR do not
 * alias the load through GPIOA_IDR. Forced to assume they might, it
 * reloads. It works BY ACCIDENT.
 *
 * Change the code so the aliasing argument goes away -- drop the stores,
 * or mark the pointers `restrict`, or read the register into a local
 * before the loop -- and it breaks exactly like CASE 1.
 *
 * "Works" and "correct" are different properties. Being able to draw
 * that distinction is the whole point of this file.
 * ------------------------------------------------------------------- */
unsigned int *GPIOA_IDR_plain  = (unsigned int *) 0x48000010;
unsigned int *GPIOB_BSRR_plain = (unsigned int *) 0x48000418;
unsigned int *GPIOB_BRR_plain  = (unsigned int *) 0x48000428;

void poll_button_as_written(void)
{
    while (1) {
        if ((*GPIOA_IDR_plain >> 10) & 0x01) *GPIOB_BRR_plain  = (1u << 14);
        else                                 *GPIOB_BSRR_plain = (1u << 14);
    }
}

/* The way it should be written. Note BSRR/BRR are write-only-ish set and
 * reset registers: writing a 1 acts, writing a 0 does nothing. So a
 * single store changes one pin with NO read-modify-write -- no race with
 * an ISR touching a different pin on the same port. That is why you use
 * BSRR instead of `ODR |= (1<<14)`. */
volatile unsigned int *GPIOA_IDR  = (volatile unsigned int *) 0x48000010;
volatile unsigned int *GPIOB_BSRR = (volatile unsigned int *) 0x48000418;
volatile unsigned int *GPIOB_BRR  = (volatile unsigned int *) 0x48000428;

void poll_button_correct(void)
{
    while (1) {
        if ((*GPIOA_IDR >> 10) & 0x01) *GPIOB_BRR  = (1u << 14);
        else                           *GPIOB_BSRR = (1u << 14);
    }
}


/* ---------------------------------------------------------------------
 * CASE 3 -- The follow-up question, and the one that catches people.
 *
 * "Does volatile make this thread-safe?"   NO.
 *
 * `counter++` is a read-modify-write: load, add, store. volatile forces
 * the load and the store to actually happen, but it does NOT make the
 * three steps indivisible. If an ISR fires between the load and the
 * store, that increment is lost.
 *
 * Fix: a critical section (mask interrupts around it -- PRIMASK or
 * BASEPRI on Cortex-M), or an atomic, or on ARM a LDREX/STREX pair.
 *
 * Compile with -O2 -S and count the instructions in isr_unsafe_increment:
 * you will see a load, an add and a store. Three instructions, three
 * places an interrupt can land.
 * ------------------------------------------------------------------- */
volatile unsigned int counter;

void isr_unsafe_increment(void) { counter++; }   /* NOT atomic */

/* Sketch of the fix on Cortex-M (won't assemble on x86, hence commented):
 *
 *   uint32_t primask = __get_PRIMASK();
 *   __disable_irq();
 *   counter++;
 *   __set_PRIMASK(primask);      // restore, don't blindly __enable_irq()
 *
 * Restoring the saved mask rather than unconditionally re-enabling is the
 * detail worth mentioning -- blind re-enable breaks nested critical
 * sections.
 */
