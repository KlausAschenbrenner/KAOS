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

struct _RootDirectoryEntry
{
    char Entry[32];
} __attribute__ ((packed));
typedef struct _RootDirectoryEntry RootDirectoryEntry; 

struct _RootDirectory
{
    RootDirectoryEntry Entries[224];
} __attribute__ ((packed));
typedef struct _RootDirectory RootDirectory; 

// Loads the FAT12 Root Directory
void LoadRootDirectory();

void ReadRootDirectory(int StartSector, int Sectors);

#endif
