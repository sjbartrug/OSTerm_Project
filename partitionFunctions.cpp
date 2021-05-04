#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <iostream>
#include "partitionFunctions.h"
#include "vdiFile.h"
#include "vdiHeader.h"
#include "vdiFunctions.h"

using namespace std;

struct partitionFile * partitionOpen(struct vdiFile * file, struct partitionEntry partitionInfo[]){
    int changePosition;
    struct partitionFile * partition = (struct partitionFile *) malloc(sizeof(struct partitionFile));
    partition -> file = file;
    partition -> file -> pointerPosition = file -> header.frameOffset + partitionInfo[0].logicalBlocking * 512;
    changePosition = vdiSeek(file, partition -> file -> pointerPosition, SEEK_SET);
}

int partitionSeek(struct partitionFile *f, int offset, int anchor, struct partitionEntry partitionInfo[]){
    if(anchor == SEEK_SET && offset < partitionInfo[0].numberOfSectorsInPartition*512){
        lseek(f -> file -> fileDescriptor, offset, SEEK_SET);
        return(f -> file -> pointerPosition + offset);
    }
    if(anchor == SEEK_CUR && (SEEK_CUR + offset) < partitionInfo[0].numberOfSectorsInPartition*512){
        lseek(f -> file -> fileDescriptor, offset, SEEK_CUR;
        return(f -> file -> pointerPosition + offset);
    }
    if(anchor == SEEK_END && abs(offset) < partitionInfo[0].numberOfSectorsInPartition*512){
        lseek(f -> file -> fileDescriptor, offset, SEEK_END);
        return(f -> file -> pointerPosition + offset);
    }
}

int mbrRead(struct vdiFile *f, struct mbrSector & buf, int count){
    int readBytes = vdiRead(f, &buf, sizeof(&buf));
    f -> pointerPosition = SEEK_CUR;
    if(readBytes == sizeof(&buf)){
        cout<<"Data has been read"<<"\n";
    }
    else{
        cout<<"Not all data was read"<<readBytes<<"\n";
    }
    return readBytes;
}

int mbrSeek(struct vdiFile *f, int offset, int anchor){
    if(anchor == SEEK_SET && offset <= f -> header.frameOffset + sizeof(struct mbrSector) && offset >= f-> header.frameOffset){
        f -> pointerPosition = lseek(f -> fileDescriptor, offset, anchor);
        return f -> pointerPosition;
    }
    if(anchor == SEEK_CUR && offset <= f -> header.frameOffset + sizeof(struct mbrSector) >= SEEK_CUR + offset && SEEK_CUR + offset >= f-> header.frameOffset){
        f -> pointerPosition = lseek(f -> fileDescriptor, offset, anchor);
        return f -> pointerPosition;
    }
    if(anchor == SEEK_END && offset <= f -> header.frameOffset + sizeof(struct mbrSector) >= SEEK_END + offset  && SEEK_END + offset >= f-> header.frameOffset){
        f -> pointerPosition = lseek(f -> fileDescriptor, offset, anchor);
        return f -> pointerPosition;
    }
    return -1;
}

void partitionClose(struct partitionFile *partition){
    partition = null;
    free(partition);
}
