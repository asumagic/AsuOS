#include "interrupts.hpp"
#include "../io/portio.hpp"

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
void initialize()
{
	master.sendCommand(PIC::INIT);
	slave.sendCommand(PIC::INIT);

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
}

PIC master = { 0x20, 0x20, 0x21 },
    slave  = { 0xA0, 0xA0, 0xA1 };

}
