#include <stdint.h>
#include <stdio.h>

union EXAMPLE_REGISTER
{
    uint8_t hw;
    struct __attribute__((packed))
    {                                  // Bits  Description
        uint8_t IDLE : 1;              // 0     Idle / Standby mode
        uint8_t LOW_BRIGHTNESS : 1;    // 1     Low brightness
        uint8_t NORMAL_BRIGHTNESS : 1; // 2     Normal brightness
        uint8_t HIGH_BRIGHTNESS : 1;   // 3     High brightness
        uint8_t PARTY_MODE : 1;        // 4     Party mode (LEDs flash)
        uint8_t DEBUG_MODE : 1;        // 5     Debug mode
        uint8_t RESERVED : 1;          // 6     Reserved
        uint8_t FACTORY_TEST_MODE : 1; // 7     Factory test mode
    } s;
};

int main()
{
    volatile union EXAMPLE_REGISTER reg;

    // Example usage: Set the register to PARTY_MODE
    reg.hw = 0; // Clear all bits
    reg.s.PARTY_MODE = 1;

    // Print the register value
    printf("Register value: 0x%02X\n", reg.hw);

    return 0;
}

/**
 * 1. The Core Concept

In embedded systems, hardware registers are memory addresses where individual bits or groups of bits control hardware peripherals (e.g., enabling an ADC, setting baud rates, triggering interrupts).

Usually, people manipulate bits using shifts and masks:

c
#define PARTY_MODE_BIT (1u << 4)
reg |= PARTY_MODE_BIT;   // Set bit 4
reg &= ~PARTY_MODE_BIT;  // Clear bit 4

The Union + Struct Bitfield pattern overlays two views of the exact same memory:

The raw word view (hw): Lets you read or write the entire byte / 32-bit word in one instruction (e.g., zeroing out, bulk copying, or writing to a hardware address).
The structured bit view (s): Lets the compiler generate the bit-shifts and masks for you under human-readable names.
c
union EXAMPLE_REGISTER {
    uint8_t hw;  // Both 'hw' and 's' share the EXACT same memory address
    struct __attribute__((packed)) {
        uint8_t IDLE              : 1;  // Bit 0 (LSB on little-endian)
        uint8_t LOW_BRIGHTNESS    : 1;  // Bit 1
        uint8_t NORMAL_BRIGHTNESS : 1;  // Bit 2
        uint8_t HIGH_BRIGHTNESS   : 1;  // Bit 3
        uint8_t PARTY_MODE        : 1;  // Bit 4
        uint8_t DEBUG_MODE        : 1;  // Bit 5
        uint8_t RESERVED          : 1;  // Bit 6
        uint8_t FACTORY_TEST_MODE : 1;  // Bit 7 (MSB)
    } s;
};
2. Under the Hood: What the Compiler Generates

When you write:

c
reg.s.PARTY_MODE = 1;

The compiler does not have a magic 1-bit CPU instruction (on most architectures like ARM or x86). Instead, it compiles that line into a Read-Modify-Write (RMW) sequence:

Load reg into a CPU register.
Bitwise OR with (1 << 4).
Store the result back into reg.

And when you write:

c
reg.hw = 0;

It simply issues a single MOV / STR instruction writing 0 to that memory location.

3. Multi-bit Fields (Bit Slicing)

Bitfields are not limited to 1-bit flags. You can group bits into integer ranges:

c
union UART_CTRL {
    uint32_t raw;
    struct {
        uint32_t enable    : 1;  // bit 0
        uint32_t baud_rate : 3;  // bits 1-3 (values 0 to 7)
        uint32_t parity    : 2;  // bits 4-5
        uint32_t reserved  : 26; // bits 6-31
    } bits;
};
union UART_CTRL ctrl;
ctrl.bits.baud_rate = 5; // Compiler automatically shifts 5 into bits [3:1]
4. The "Senior Engineer" Gotchas (Crucial for Interviews & Real MMIO)

While this technique looks clean, in production embedded codebases and safety-critical standards (like MISRA C or Linux Kernel style), bitfields on memory-mapped I/O (MMIO) are often used with caution or avoided entirely due to several subtle traps:

Implementation-Defined Ordering & Endianness:
The C standard explicitly states that the layout of bitfields within an integer is implementation-defined.
On GCC/Clang on Little-Endian (ARM Cortex-M, x86), bitfields are packed from LSB to MSB.
On Big-Endian platforms or certain DSP compilers, the first declared field might be placed at the MSB!
Hidden Read-Modify-Write (RMW) Hazards:
Some hardware registers have Write-1-to-Clear (W1C) bits (common in interrupt status registers).
If you write status_reg.bits.error_ack = 1;, the compiler reads the entire register and writes it back with that bit set. If other interrupt flags were active, the write-back will inadvertently clear all other active interrupts!
No Bit-Level Pointers or Atomic Access:
You cannot take the address of a bitfield (&reg.s.PARTY_MODE is a compile error).
Bitfield accesses are not atomic. If an interrupt routine modifies reg.s.DEBUG_MODE while the main loop modifies reg.s.PARTY_MODE, a race condition will corrupt the register.
Padding & Alignment:
Without __attribute__((packed)) (or compiler pragmas), compilers may add padding between fields or align to 32-bit boundaries unexpectedly.
🧠 Knowledge Check Quiz

Test your understanding with these 5 quick questions. Try answering them, and we'll review your answers!

Question 1: Value Calculation

Given the code in c_bitpacking.c:

c
reg.hw = 0;
reg.s.PARTY_MODE = 1;
reg.s.HIGH_BRIGHTNESS = 1;

What is the hexadecimal value printed by printf("0x%02X\n", reg.hw);?

Question 2: Multi-bit Overflow

Suppose you define:

c
struct {
    uint8_t mode : 2; // a 2-bit field
} s;
s.mode = 5;

What value will actually be stored in s.mode?

Question 3: Pointer to Bit

Can you pass a specific bitfield to a function expecting a pointer, like this?

c
void toggle(uint8_t *flag);
toggle(&reg.s.PARTY_MODE);

Why or why not?

Question 4: Memory Mapping & Volatile

If this register represents a physical hardware register at memory address 0x40001000, how would you declare a pointer to access it correctly in C so the compiler doesn't optimize away reads/writes?

Question 5: Real-World Gotcha

Suppose bit 7 of a status register is TX_COMPLETE, which hardware defines as:

"Write 1 to clear this interrupt flag; writing 0 has no effect."

If bit 0 is RX_ENABLE, what potential bug occurs if you execute:

c
status_reg.s.RX_ENABLE = 1;

(Hint: Think about what the CPU actually does under the hood when writing to a bitfield).
 */