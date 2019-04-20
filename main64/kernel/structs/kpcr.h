//
//  KPCR.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 20.04.2019.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#ifndef KPCR_H
#define KPCR_H

// Represents the Processor Control Region (PCR)
typedef struct _KPCR
{
    // A pointer to the IDT data structure
    long *IDT;

    // A pointer to the GDT data structure
    long *GDT;

    // A pointer to the TSS data structure
    long *TSS;
} KPCR;

// Moves the KPCR pointer to the R14 register
extern void MoveKPCRToRegister(long kpcrAddress);

// Returns the KPCR pointer from the R14 register
extern long GetKPCR();

// Dumps out the KPCR data structure
void DumpKPCR();

#endif