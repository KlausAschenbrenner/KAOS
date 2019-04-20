//
//  kpcr.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 20.04.2019.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#include "kpcr.h"

// Dumps out the KPCR data structure
void DumpKPCR()
{
    KPCR *kpcr = (KPCR *)GetKPCR();
    char str[32] = "";

    printf("IDT: 0x");
    printf_long(kpcr->IDT, 16);
    printf("\n");

    printf("GDT: 0x");
    ltoa(kpcr->GDT, 16, str);
    printf(str);
    printf("\n");

    printf("TSS: 0x");
    printf_long(kpcr->TSS, 16);
    printf("\n");
}