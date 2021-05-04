#ifndef MBR
#define MBR
#include "partitionData.h"
#include "vdiFile.h"
#pragma pack(1)

const unsigned short BOOT_SECTOR_MAGIC = 0xaa55;

struct mbrSector{
    unsigned char bootStrapCode[446];
    struct partitionEntry partitionEntryInfo[4];
    uint16_t bootSignature;
};

struct __attribute__((packed)) partitionFile{
    struct vdiFile * file;
    struct partitionEntry partitionEntryInfo[4];
};

#endif