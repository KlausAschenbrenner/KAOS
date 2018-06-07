#include "drivers/common.h"
#include "drivers/screen.h"
#include "drivers/keyboard.h"
#include "drivers/floppy.h"
#include "kaosldr.h"

// Implemented in Assembly
extern void SwitchToLongMode();

// Main function of KAOSLDR.BIN
void k_main()
{
    // Initializes the screen
	InitializeScreen();
    
    // Initializes the ISR & IRQ routines
    InitIdt();
    
    // Disable the hardware interrupts
    DisableInterrupts();
    
    // Initializes the PIC, and remap the IRQ handler
    PICInitialize(0x20, 0x28);
    
    // Initialize the keyboard
    InitKeyboard();
    
    // Enable the hardware interrupts again
    EnableInterrupts();

	// Install the Floppy IRQ Handler
	flpydsk_install();
    
	// Loads the x64 Kernel into Memory
	LoadKernelIntoMemory();

	// Switches the CPU into x64 Long Mode, and finally executes the x64 Kernel
	SwitchToLongMode();
}