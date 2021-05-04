//
// Created by bob on 1/18/21.
//

#include <stdio.h>
#include <stddef.h>
#include <fcntl.h>
#include "testVDI.h"
#include "dumpBytes.h"

//-----------------------------------------------------------------------------
// char *uuid2ascii(uint8_t *uuid)
//  convert UUID to ascii hex form
//
// Parm
//  uuid - 16-byte uuid
//
// Returns
//  pointer to statically allocated character string with hex form of uuid
//
// Notes
// - Is not reentrant, uses a single static buffer
//

static char
    uuidStr[40];

char *uuid2ascii(struct UUID *uuid) {

    sprintf(uuidStr,"%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x"
                    "-%02x%02x%02x%02x%02x%02x",
            uuid->timeLow[0],uuid->timeLow[1],uuid->timeLow[2],uuid->timeLow[3],
            uuid->timeMid[0],uuid->timeMid[1],
            uuid->timeHigh[0],uuid->timeHigh[1],
            uuid->clock[0],uuid->clock[1],
            uuid->node[0],uuid->node[1],uuid->node[2],uuid->node[3],
            uuid->node[4],uuid->node[5]);
    return uuidStr;
}

//-----------------------------------------------------------------------------
// void vdiDumpHeader(struct VDI_File *f)
//  Display the VDI header structure
//
// Parm
//  f - pointer to opened VDI file
//

void vdiDumpHeader(struct VDIFile *f) {

    printf("      Image name: [%-64.64s]\n",f->header->fileInfo);
    printf("       Signature: 0x%08x\n",f->header->magic);
    printf("         Version: %d.%02d\n",f->header->versionMajor,
           f->header->versionMinor);
    printf("     Header size: 0x%08x  %d\n",f->header->postHeaderSize,
           f->header->postHeaderSize);
    printf("      Image type: 0x%08x\n",f->header->imageType);
    printf("           Flags: 0x%08x\n",f->header->imageFlags);
    printf("     Virtual CHS: %d-%d-%d\n",f->header->oldGeometry.nCylinders,
           f->header->oldGeometry.nHeads,f->header->oldGeometry.nSectors);
    printf("     Sector size: 0x%08x  %d\n",
           f->header->oldGeometry.bytesPerSector,
           f->header->oldGeometry.bytesPerSector);
    printf("     Logical CHS: %d-%d-%d\n",f->header->diskGeometry.nCylinders,
           f->header->diskGeometry.nHeads,f->header->diskGeometry.nSectors);
    printf("     Sector size: 0x%08x  %d\n",
           f->header->diskGeometry.bytesPerSector,
           f->header->diskGeometry.bytesPerSector);
    printf("      Map offset: 0x%08x  %d\n",f->header->mapOffset,
           f->header->mapOffset);
    printf("    Frame offset: 0x%08x  %d\n",f->header->dataOffset,
           f->header->dataOffset);
    printf("      Frame size: 0x%08x  %d\n",f->header->pageSize,
           f->header->pageSize);
    printf("Extra frame size: 0x%08x  %d\n",f->header->extraPageSize,
           f->header->extraPageSize);
    printf("    Total frames: 0x%08x  %d\n",f->header->nPagesTotal,
           f->header->nPagesTotal);
    printf("Frames allocated: 0x%08x  %d\n",f->header->nPagesAllocated,
           f->header->nPagesAllocated);
    printf("       Disk size: 0x%016lx  %lu\n",f->header->diskSize,
           f->header->diskSize);
    printf("            UUID: %s\n",uuid2ascii(&f->header->uuidCreate));
    printf("  Last snap UUID: %s\n",uuid2ascii(&f->header->uuidModify));
    printf("       Link UUID: %s\n",uuid2ascii(&f->header->uuidPrevImage));
    printf("     Parent UUID: %s\n",uuid2ascii(&f->header->uuidPrevImageModify));
    printf("   Image comment:\n");
    displayBufferPage((uint8_t *)(f->header->comment),256,0,
//                      (uint8_t *)&(f->header->comment) -
//                      (uint8_t *)&(f->header));
                      offsetof(struct VDIHeader,comment));
    printf("          Unused: %d\n",f->header->unused);
}

void testVDI(char *fn) {
    uint8_t
        mbr[512];
    struct VDIFile
        *f;

    f = vdiOpen(fn);

    puts("Dump of VDI header:");
    vdiDumpHeader(f);

    puts("\n\nHeader in binary:");
    displayBuffer((uint8_t *)(f->header),400,0);

    puts("\n\nTranslation map:");
    displayBuffer((uint8_t *)(f->pageMap),512,0);

    puts("\n\nPartition table from Master Boot Record:");

    vdiSeek(f,256,SEEK_SET);
    vdiRead(f,mbr,256);
    displayBufferPage(mbr,64,190,256);

    vdiClose(f);
}
