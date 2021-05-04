#ifndef OS_PROJECT_VDIFUNCTIONS_H
#define OS_PROJECT_VDIFUNCTIONS_H
#include "vdiFile.h"
#include "vdiHeader.h"

struct vdiFile * vdiOpen(char * fn);

void vdiClose(struct vdiFile * f);
void dumpVDIHeader(struct vdiFile * f);
int vdiRead(struct vdiFile * f, void * buf, int count);
int vdiSeek(struct vdiFile * f, void * buf, int count);
int vdiWrite(struct vdiFile * f, void * buf, int count);

#endif