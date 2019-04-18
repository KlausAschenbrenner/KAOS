//
//  gdt.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 18.04.2019.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#ifndef KAOS_gdt_h
#define KAOS_gdt_h

#define GDT_START_OFFSET 0x99000

/// This segment is a data segment
#define GDT_FLAG_DATASEG	0x02

/// This segment is a code segment
#define GDT_FLAG_CODESEG	0x0a
#define GDT_FLAG_TSS		0x09
#define GDT_FLAG_TSS_BUSY	0x02
#define GDT_FLAG_SEGMENT	0x10

/// Privilege level: Ring 0 
#define GDT_FLAG_RING0		0x00

/// Privilege level: Ring 1
#define GDT_FLAG_RING1		0x20

/// Privilege level: Ring 2 
#define GDT_FLAG_RING2		0x40

/// Privilege level: Ring 3 
#define GDT_FLAG_RING3		0x60

/// Segment is present
#define GDT_FLAG_PRESENT        0x80

/// Segment was accessed
#define GDT_FLAG_ACCESSED       0x01

/** 
 * @brief Granularity of segment limit 
 * - set: segment limit unit is 4 KB (page size)
 * - not set: unit is bytes
 */
#define GDT_FLAG_4K_GRAN	0x80

/**
 * @brief Default operand size 
 * - set: 32 bit
 * - not set: 16 bit
 */
#define GDT_FLAG_16_BIT		0x00
#define GDT_FLAG_32_BIT		0x40
#define GDT_FLAG_64_BIT		0x20

#define GDT_ENTRIES	6

typedef struct
{
    unsigned short LimitLow;            // 16 Bits
    unsigned short BaseLow;             // 16 Bits
    unsigned char BaseMiddle;           // 8 Bits
    unsigned char Access;               // 8 Bits
    unsigned char Granularity;          // 8 Bits
    unsigned char BaseHigh;             // 8 Bits
} __attribute__ ((packed)) GdtEntry;

typedef struct
{
    unsigned short Limit;
    unsigned long Base;
} __attribute__ ((packed)) GdtPointer;

// Initializes the GDT
void InitGdt();

// Loads the GDT table into the processor register (implemented in Assembler)
extern void GdtFlush(unsigned long);

#endif