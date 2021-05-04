#include "inodeFunctions.h"

using namespace std;

bool inodeFree(unsigned char* bitMap, unsigned int blockSize, unsigned int inodeBlockOffset, unsigned int & address){
    for(int i = 0; i < blockSize; i++){
        unsigned char currentByte = *(bitMap + i);
        for(int j = 0; j < blockSize; j++){
            if(!((currentByte >> j) & 0x1)){
                address = (inodeBlockOffset + i * 8 + j) + 1;
                *(bitMap + i) = ((1 << j) | currentByte);
                return true;
            }
        }
    }
    return false;
}

