#ifndef OS_PROJECT_VDIFILE_H
#define OS_PROJECT_VDIFILE_H
#include "vdiHeader.h"
#include <fstream>
#pragma pack(1)

struct vdiFile{
    int pageSize;
    int fileDescriptor;
    int pointerPosition;
    vdiHeader header;
};


#endif //OS_PROJECT_VDIFILE_H
