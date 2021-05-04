//
// Created by bob on 1/18/21.
//

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "testDump.h"
#include "dumpBytes.h"

void testDump(char *fn) {
    int32_t
        fd,
        mapOffset,
        dataOffset,
        pageSize,
        map[128];
    uint8_t
        mbr[512];

    fd = open(fn,O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }

    lseek(fd,340,SEEK_SET);
    read(fd,&mapOffset,sizeof(mapOffset));
    read(fd,&dataOffset,sizeof(dataOffset));
    lseek(fd,376,SEEK_SET);
    read(fd,&pageSize,sizeof(pageSize));

    printf("Map offset: %d = %x\n\n\n",mapOffset,mapOffset);

    lseek(fd,mapOffset,SEEK_SET);
    read(fd,map,sizeof(map));

    puts("Translation map:");
    displayBuffer((uint8_t *)map,512,mapOffset);

    printf("Data offset: %d = %x\n\n\n",dataOffset,dataOffset);
    printf("map[0] = %d   page size = %d\n\n\n",map[0],pageSize);

    lseek(fd,dataOffset+map[0]*pageSize,SEEK_SET);
    read(fd,mbr,sizeof(mbr));

    puts("\n\nPartition table and signature:");
    displayBufferPage(mbr+256,66,190,256);

    close(fd);
}