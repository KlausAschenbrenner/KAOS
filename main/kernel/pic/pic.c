//
//  pic.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 23.02.2014.
//  Copyright (c) 2014 Klaus Aschenbrenner. All rights reserved.
//

#include "pic.h"

// Sends a command to the PICs
static void PICSendCommand(unsigned char cmd, unsigned char picNum)
{
	if (picNum > 1)
		return;
    
	unsigned char reg = (picNum == 1) ? I86_PIC2_REG_COMMAND : I86_PIC1_REG_COMMAND;
	outb(reg, cmd);
}


// Sends data to PICs
static void PICSendData(unsigned char data, unsigned char picNum)
{
	if (picNum > 1)
		return;
    
	unsigned char reg = (picNum == 1) ? I86_PIC2_REG_DATA : I86_PIC1_REG_DATA;
	outb(reg, data);
}


// Reads data from PICs
static unsigned char PICReadData(unsigned char picNum)
{
	if (picNum > 1)
		return 0;
    
	unsigned char reg = (picNum == 1) ? I86_PIC2_REG_DATA : I86_PIC1_REG_DATA;
	return inb(reg);
}

// Initializes the PIC
void PICInitialize(unsigned char base0, unsigned char base1)
{
	unsigned char icw = 0;
    
	// Begin initialization of PIC
	icw = (icw & ~I86_PIC_ICW1_MASK_INIT) | I86_PIC_ICW1_INIT_YES;
	icw = (icw & ~I86_PIC_ICW1_MASK_IC4) | I86_PIC_ICW1_IC4_EXPECT;
    
	PICSendCommand(icw, 0);
	PICSendCommand(icw, 1);
    
	// Send initialization control word 2. This is the base addresses of the irq's
	PICSendData(base0, 0);
	PICSendData(base1, 1);
    
	// Send initialization control word 3. This is the connection between master and slave.
	// ICW3 for master PIC is the IR that connects to secondary pic in binary format
	// ICW3 for secondary PIC is the IR that connects to master pic in decimal format
	PICSendData(0x04, 0);
	PICSendData(0x02, 1);
    
	// Send Initialization control word 4.
    // Enables i86 mode.
	icw = (icw & ~I86_PIC_ICW4_MASK_UPM) | I86_PIC_ICW4_UPM_86MODE;
	PICSendData(icw, 0);
	PICSendData(icw, 1);
}