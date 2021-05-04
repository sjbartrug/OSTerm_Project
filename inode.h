#ifndef INODE
#define INODE
#pragma pack(1)

struct inode{
    unsigned short i_uid;
    unsigned int i_size;
    uint16_t i_mode;
    uint16_t i_gid;
    uint16_t i_links_count;
    uint16_t i_osd2 [6];
    uint32_t i_atime;
    uint32_t i_ctime;
    uint32_t i_mtime;
    uint32_t i_dtime;
    uint32_t i_blocks;
    uint32_t i_flags;
    uint32_t i_osd1;
    uint32_t i_block[15];
    uint32_t i_generation;
    uint32_t i_file_ac1;
    uint32_t i_dir_ac1;
    uint32_t i_faddr;
    uint32_t i_atime;
};

#endif