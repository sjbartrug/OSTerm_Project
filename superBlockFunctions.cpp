#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <iostream>
#include "partitionFunctions.h"
#include "vdiFile.h"
#include "mbr.h"
#include "vdiHeader.h"
#include "vdiFunctions.h"
#include "superBlockFunctions.h"

using namespace std;

int readSuperBlock(struct ext2File * ext2, uint32_t blockNumber, struct vdiFile *file, struct mbrSector mbr, int translationMapData[]){
    int finalResult;
    int virtualAddress =  mbr.partitionEntryInfo[0].logicalBlocking * 512 + 1024;
    int physicalAddress = actualPage(virtualAddress, file, translationMapData);
    vdiSeek(file, physicalAddress, SEEK_SET);
    finalResult = vdiRead(file, &(ext2 -> superblock), sizeof(ext2 -> superblock));
    if(finalResult != 1){
        return -1;
    }
    return 0;
}

int actualPage(int virtualAddress, struct vdiFile * file, int translationMapData[]){
    int physicalPageNumber, offsetToPhysicalPage, physicalAddress;
    physicalPageNumber = translationMapData[virtualAddress / file -> header.frameSize];
    if(physicalPageNumber == -1 || physicalPageNumber == -2){
        lseek(file -> fileDescriptor, 0, SEEK_END);
        write(file -> fileDescriptor, 0, file -> header.frameSize);
        translationMapData[virtualAddress / file -> header.frameSize] = file -> header.frameAllocated;
        file -> header.frameAllocated++;
    }
    offsetToPhysicalPage = (virtualAddress)%file -> header.frameSize;
    physicalAddress = file -> header.frameOffset + physicalPageNumber * file -> header.frameSize + offsetPhysicalPage;
    return physicalAddress;
}

void writeSuperBlock(vdiFile* f, BootSector boot, unsigned int vdiMap[], ext2_super_block & superBlock){
    unsigned int superBlockLocation = computeLocation(1024, f, boot, vdiMap);
    if (lseek(f -> file, superBlockLocation, SEEK_SET) < 0){
        cout << "Cannot seek to the superblock" << endl;
        return 1;
    }
    if (write(f -> file, & superBlock, sizeof(superBlock)) != 1024){
        cout << "Superblock was not written properly" << endl;
        return 1;
    }
    return 0;
}