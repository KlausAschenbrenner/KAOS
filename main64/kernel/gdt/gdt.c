//
//  gdt.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 18.04.2019.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#include "gdt.h"
#include "tss.h"

// The GDT Entries - starting at 0x99000
GdtEntry *_gdtEntries = (GdtEntry *)GDT_START_OFFSET;

// TSSEntry *_tssEntry = (TSSEntry *)0x99500;
static TSSEntry _tssEntry;

// The pointer that points to the GDT Entries
GdtPointer _gdtPointer;

// Installs the various need GDT Entries
void InitGdt()
{
    _gdtPointer.Limit = sizeof(GdtEntry) * GDT_ENTRIES - 1;
    _gdtPointer.Base = (unsigned long)_gdtEntries;
    memset(_gdtEntries, 0, sizeof(GdtEntry) * GDT_ENTRIES);

    memset(&_tssEntry, 0, sizeof(TSSEntry));
    _tssEntry.rsp0 = 0xFFFF800000050000 - 0x10;

    // The NULL Descriptor
    GdtSetGate(0, 0, 0, 0, 0);

    // The Code Segment Descriptor for Ring 0
    // #define GDT_FLAG_RING0		0x00    0000 0000
    // #define GDT_FLAG_SEGMENT	    0x10    0001 0000
    // #define GDT_FLAG_CODESEG	    0x0A    0000 1010
    // #define GDT_FLAG_PRESENT     0x80    1000 0000
    //                                      1001 1010: 0x9A
    GdtSetGate(1, 0, 0, GDT_FLAG_RING0 | GDT_FLAG_SEGMENT | GDT_FLAG_CODESEG | GDT_FLAG_PRESENT, GDT_FLAG_64_BIT);

    // The Data Segment Descriptor for Ring 0
    // #define GDT_FLAG_RING0		0x00    0000 0000
    // #define GDT_FLAG_SEGMENT	    0x10    0001 0000
    // #define GDT_FLAG_DATASEG	    0x02    0000 0010
    // #define GDT_FLAG_PRESENT     0x80    1000 0000
    //                                      1001 0010: 0x92
    GdtSetGate(2, 0, 0, GDT_FLAG_RING0 | GDT_FLAG_SEGMENT | GDT_FLAG_DATASEG | GDT_FLAG_PRESENT, 0);

    // The Code Segment Descriptor for Ring 3
    GdtSetGate(3, 0, 0, GDT_FLAG_RING3 | GDT_FLAG_SEGMENT | GDT_FLAG_CODESEG | GDT_FLAG_PRESENT, GDT_FLAG_64_BIT);

    // The Data Segment Descriptor for Ring 3
    GdtSetGate(4, 0, 0, GDT_FLAG_RING3 | GDT_FLAG_SEGMENT | GDT_FLAG_DATASEG | GDT_FLAG_PRESENT, 0);

    // The TSS Entry
    GdtSetGate(5, &_tssEntry, sizeof(TSSEntry) - 1, 0x89, 0x40);

    // Install the new GDT
    GdtFlush((unsigned long)&_gdtPointer);
}

// Sets the GDT Entry
void GdtSetGate(unsigned char Num, unsigned long Base, unsigned long Limit, unsigned char Access, unsigned char Granularity)
{
    _gdtEntries[Num].BaseLow = Base & 0xFFFF;
    _gdtEntries[Num].BaseMiddle = ((Base >> 16) & 0xFF);
    _gdtEntries[Num].BaseHigh = ((Base >> 24) & 0xFF);
    _gdtEntries[Num].LimitLow = Limit & 0xFFFF;
    _gdtEntries[Num].Granularity = ((Limit >> 16) & 0x0F);
    _gdtEntries[Num].Granularity |= (Granularity & 0xF0);
    _gdtEntries[Num].Access = Access;
}