#include "interrupts.hpp"
#include "../io/portio.hpp"
#include "../common/kernel.hpp"

namespace interrupts
{

void PIC::sendCommand(commands cmd)
{
	io::outByte(cmdport, cmd);
}

void PIC::sendData(uint8_t data)
{
	io::outByte(dataport, data);
}

uint8_t PIC::readData()
{
	return io::inByte(dataport);
}

void eoi(uint8_t irq)
{
	if (irq >= 8)
		slave.sendCommand(PIC::EOI);

	master.sendCommand(PIC::EOI);
}

// Remap to avoid IRQs conflicting with CPU exceptions
// Do IDT initializations
void initialize()
{
	//master.sendCommand(PIC::INIT); // Is this even the correct way?
	//slave.sendCommand(PIC::INIT);

	uint8_t mr1 = master.readData(), mr2 = slave.readData();

	PIC::commands initcmd = (PIC::commands)((uint8_t)PIC::ICW1_INIT + (uint8_t)PIC::ICW1_ICW4);
	master.sendCommand(initcmd);
	slave.sendCommand(initcmd);
	master.sendData(0x08);
	slave.sendData(0x70);
	master.sendData(4);
	slave.sendData(2);
	master.sendData(static_cast<uint8_t>(PIC::ICW4_8086));
	slave.sendData(static_cast<uint8_t>(PIC::ICW4_8086));
	master.sendData(mr1);
	slave.sendData(mr2);

	for (uint16_t i = 0; i < 256; ++i)
	{
		uint64_t addr = Kernel::getObject()->queryISRHandler(i);

		idtentries[i].segmentselector = 0x08;
		if (addr)
		{
			idtentries[i].typeattrib.present = true;
			idtentries[i].offsetlow =    addr &         0xFFFF;
			idtentries[i].offsetmiddle = (addr >> 16) & 0xFFFFFFFF;
			idtentries[i].offsethigh =   (addr >> 24) & 0xFFFFFFFF;
		}
		else
		{
			idtentries[i].typeattrib.present = false;
		}

		idtentries[i].typeattrib.zero = 0;
		idtentries[i].typeattrib.attribute = 0b1110;
		idtentries[i].typeattrib.ring = 0;
		
	}	

	loadidt();

	// Once we're done with initializing the IDT & co
	asm volatile("sti");

	while(true);
}

void loadidt()
{
	asm volatile("lidt %0" :: "m"(idtptr));
}

PIC master = { 0x20, 0x20, 0x21 },
    slave  = { 0xA0, 0xA0, 0xA1 };

IDTPointer idtptr = { (sizeof(IDTEntry) * 8 * 256 - 1), idtentries }; // Bytes * bits * entries - 1
IDTEntry idtentries[256];

}
