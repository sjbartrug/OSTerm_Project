#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "vdiFunctions.h"

using namespace std;

struct VDIFile *vdiOpen(char *fn){
    int fileName;
    struct VDIFile * file = (struct vdiFile *) malloc(sizeof (struct vdiFile));
    fileName = open(fn,O_RDWR);
    file -> fileName = fileName;
    if(fileName == -1){
        cout << "Cannot open the file\n";
        return null;
    }
    return file;
}

void vdiClose(struct vdiFile *f){
    close(f -> fileName);
}

ssize_t vdiRead(struct vdiFile *f, void * buf, ssize_t count){
    ssize_t numberOfBytes;
    numberOfBytes = read(f -> fileName, buf, count);
    f -> pointerPosition = SEEK_CUR;
    if(numberOfBytes == -1){
        cout << "Cannot read the file\n";
        return 0;
    }
    return numberOfBytes;
}

off_t vdiSeek(vdiFile* f, off_t offset, int whence){
    off_t location;
    if(whence == SEEK_SET){
        location = lseek(f -> fileName, offset, whence);
        if(location < 0)
        {
            cout << "Cannot find the header\n";
            return 1;
        }
        f -> cursor = location;
    }
    if(whence == SEEK_CUR){
        location = lseek(f -> fileName, offset, whence);
        if(location < 0)
        {
            cout << "Cannot find the header\n";
            return 1;
        }
        f -> cursor = offset;
    }
    if(whence == SEEK_CUR){
        location = lseek(f -> fileName, offset, whence);
        if(location < 0)
        {
            cout << "Cannot find the header\n";
            return 1;
        }
        f -> cursor = offset + f -> fileSize;
    }
}




