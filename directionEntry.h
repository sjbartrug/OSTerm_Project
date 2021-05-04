#ifndef OS_PROJECT_DIRECTIONENTRY_H
#define OS_PROJECT_DIRECTIONENTRY_H

struct __attribute__((packed))Entry{
    uint32_t inodeNumber;
    uint16_t recordLength;
    uint8_t nameLength;
    uint8_t file_type;
    unsigned char name[255];
};

#endif