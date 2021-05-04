//
// Created by bob on 1/18/21.
//

#ifndef FILESYSTEMS_TESTVDI_H
#define FILESYSTEMS_TESTVDI_H

#include "vdiFile.h"

#ifdef __cplusplus
    extern "C" {
#endif

void
    vdiDumpHeader(struct VDIFile *),
    testVDI(char *);
char *
    uuid2ascii(struct UUID *uuid);

#ifdef __cplusplus
    };
#endif

#endif //FILESYSTEMS_TESTVDI_H
