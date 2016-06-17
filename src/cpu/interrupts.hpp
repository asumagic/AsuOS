#ifndef HINTERRUPTS
#define HINTERRUPTS

#include <stdint.h>

#define FAST_PIC_INIT // Older hardware may need time between PIC commands.

namespace interrupts
{

// @TODO : Use processor-APIC & IOAPIC to replace the PIC code in the future.
// Probably unneeded as long we don't have multicore or if we don't need such advanced features

// Programmable Interruption Controller struct
struct PIC
{
	uint8_t addr, cmdport, dataport;
	enum commands // @TODO rename because they aren't only commands.
	{
		EOI = 0x20, // End Of Interrupt

		// Initialization command words
		ICW1_ICW4 = 0x01,       // ICW4 needed?
		ICW1_SINGLE = 0x02,     // Single cascade mode
		ICW1_INTERVAL4 = 0x04,  // Call address interval 4 (8) - often ignored
		ICW1_LEVEL = 0x08,      // Level-triggered mode
		ICW1_INIT = 0x10,       // Initialization

		ICW4_8086 = 0x01,       // 8086 mode
		ICW4_AUTOEOI = 0x02,    // Automatic EOI mode
		ICW4_BUF_SLAVE = 0x08,  // Buffered slave mode
		ICW4_BUF_MASTER = 0x0c, // Buffered master mode
		ICW4_SFNM = 0x10,       // Special Fully Nested Mode (for high counts of cascaded controllers)
	};

	void sendCommand(commands cmd); // Send a command to the PIC
	void sendData(uint8_t data); // Send data to the pic

	uint8_t readData(); // Read data from the PIC
};

extern PIC master, slave;

void eoi(uint8_t irq); // End Of Interrupt, determines which PIC the EOI should be sent to

void initialize(); // Initialize PICs

}

#endif
