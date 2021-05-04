#ifndef OS_PROJECT_PARTITIONFUNCTIONS_H
#define OS_PROJECT_PARTITIONFUNCTIONS_H

#include "partitionFunctions.h"
#include "vdiFile.h"
#include "vdiHeader.h"
#include "vdiFunctions.h"
#include "partitionFunctions.h"

struct partitionFile * partitionFileOpen(struct vdiFile *file, struct partitionEntry);
int partitionSeek(struct partitionFile *f, int offset, int anchor, struct partitionEntry partitionInfo[]);
int mbrSeek(struct vdiFile *f, struct partitionFile *partition);
int mbrSeek(struct vdiFile *f, int offset, int anchor);
void partitionClose(struct partitionFile *partition);

//void displayPartitionInfo(struct mbrSector mbrData);
//void displaySuperBlock(struct vdiFile *f, struct dataBlock data, struct mbrSector mbrData);

#endif //OS_PROJECT_PARTITIONFUNCTIONS_H
