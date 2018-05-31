//
//  fat12.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 20.05.2018.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#ifndef KAOS_Fat12_h
#define KAOS_Fat12_h

const int NumberOfFATs = 2;
const int SectorsPerFAT = 9;
const int ReservedSectors = 1;
const int RootEntries = 224;
const int BytesPerSector = 512;

struct T_RootDirectoryEntry
{
    char Entry[32];
} __attribute__ ((packed));
typedef struct T_RootDirectoryEntry RootDirectoryEntry; 

struct T_RootDirectory
{
    RootDirectoryEntry Entries[224];
} __attribute__ ((packed));
typedef struct T_RootDirectory RootDirectory; 

// Loads the FAT12 Root Directory
void LoadRootDirectory();

#endif
