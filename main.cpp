#include <iostream>
#include "testVDI.h"

using namespace std;

struct cdiFile * vdiOpen(char *fn);
void vdiClose(struct vdiFile *f);
ssize_t vdiRead(struct vdiFile *f, void * buf, ssize_t count);
off_t vdiSeek(vdiFile* f, off_t offset, int whence);

struct  paritionFile * partitionFileOpen(struct vdiFile *file, struct partitionEntry);
int partitionSeek(struct paritionFile *f, int offset, int anchor, struct partitionEntry partitionInfo[]);
void partitionClose(struct partitionFile *partition);

int main()
{
    int open(char *fn, int mode);
    void close(int fd);
    ssize_t read(int fd, void *buf, size_t count);
    ssize_t write(int fd, void *buf, size_t count);
    off_t lseek(int fd, off_t offset, int anchor);
    void displayBufferPage(uint8_t *buf, uint32_t count, uint32_t skip, uint64_t offset);
    void displayBuffer(uint8_t *buf, uint32_t count, uint64_t offset);

    ssize_t vdiRead(struct VDIFile *f,void *buf,size_t count);
    ssize_t vdiWrite(struct VDIFile *f, void *buf, size_t count);
    struct VDIFile *vdiOpen(char *fn);
    void vdiClose(struct VDIFile *f);
    off_t vdiSeek(VDIFile *f,off_t offset,int anchor);

    struct PartitionFile *partitionOpen(struct VDIFile *,struct PartitionEntry);
    void partitionClose(struct PartitionFile *f);
    ssize_t partitionRead(struct PartitionFile *f,void *buf,size_t count);
    ssize_t partitionWrite(struct PartitionFile *f,void *buf,size_t count);
    off_t partitionSeek(struct PartitionFile *f,off_t offset,int anchor);

    struct Ext2File *ext2Open(char *fn,int32_t pNum);
    void ext2Close(struct Ext2File *f);
    int32_t fetchBlock(struct Ext2File *f,uint32_t blockNum, void *buf);
    int32_t writeBlock(struct Ext2File *f,uint32_t blockNum, void *buf);
    int32_t fetchSuperblock(struct Ext2File *f,uint32_t blockNum,struct Ext2Superblock *sb);
    int32_t writeSuperblock(struct Ext2File *f,uint32_t blockNum,struct Ext2Superblock *sb);
    int32_t fetchBGDT(struct Ext2File *f,uint32_t blockNum,struct Ext2BlockGroupDescriptor *bgdt);
    int32_t writeBGDT(struct Ext2File *f,uint32_t blockNum,struct Ext2BlockGroupDescriptor *bgdt);

    int32_t fetchInode(struct Ext2File *f,uint32_t iNum,struct Inode *buf);
    int32_t writeInode(struct Ext2File *f,uint32_t iNum,struct Inode *buf);

    int32_t inodeInUse(struct Ext2File *f,uint32_t iNum);
    uint32_t allocateInode(struct Ext2File *f,int32_t group);
    int32_t freeInode(struct Ext2File *f,uint32_t iNum);

    int32_t fetchBlockFromFile(struct Inode *i,uint32_t bNum, void *buf);
    int32_t writ;

    struct Directory *openDir(uint32_t iNum);
    bool getNextDirent(struct Directory *d,uint32_t &iNum,char *name);
    void rewindDir(struct Directory *d);
    void closeDir(struct Directory *d);

    uint32_t searchDir(struct Ext2File *f,uint32_t iNum,char *target);
    uint32_t traversePath(Ext2File *f,char *path);
}
