//
//  tss.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 18.04.2019.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

typedef struct
{
    int reserved1;
    long rsp0;
    long rsp1;
    long rsp2;
    long reserved2;
    long ist1;
    long ist2;
    long ist3;
    long ist4;
    long ist5;
    long ist6;
    long ist7;
    long reserved3;
    int reserved4;
} __attribute__ ((packed)) TSSEntry;