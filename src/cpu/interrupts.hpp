#ifndef HINTERRUPTS
#define HINTERRUPTS

#include <stdint.h>

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
		EOI = 0x20, // End Of Interrupt,

		INIT = 0x11, // init the PIC

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

struct IDTEntry;

// IDT pointer used by lidt
struct IDTPointer
{
	uint16_t size; // IDT size in bytes -1
	IDTEntry* address; // Address to the IDT
} __attribute__((packed));

// The offset is split in two accross the IDT in compatibility/long mode.
// It consists of a 64-bit address, its segment selector and the type & attributes.
// Type & Attribute byte :
// - 4 bit gate type
// - Storage segment bit
// - 2 bit descriptor priviledge level (specifies which rings can call the gate).
// - Present bit (0 if unused)
struct IDTEntry
{
	uint16_t offsetlow; // Low part of the offset
	uint16_t segmentselector;
	uint8_t  unused;
	uint8_t  typeattrib;
	uint16_t offsetmiddle; // Low and high part of the pointer pointing to the interruption handler
	uint32_t offsethigh;
	uint32_t unusedbis;
} __attribute__((packed));

extern PIC master, slave;

void eoi(uint8_t irq); // End Of Interrupt, determines which PIC the EOI should be sent to

void initialize(); // Initialize PICs

void loadidt();

void hang();

extern "C" {
	extern IDTPointer idtptr;
	extern IDTEntry idtentries[256];
}

}

#endif
