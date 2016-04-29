//
// Created by tlh on 2016/4/29.
//

#include "BitStream.h"

bool BitStream::getBit(bool& data) {
    if (stream.empty()&&!feof(fin)) {
        _getNewByte();
    }
    if (stream.empty()){
        return false;
    }
    data = stream.front();
    stream.pop();
    return true;
}

void BitStream::_getNewByte() {
    //一个字节对应的二进制数串
    bool bitCode[8];
    int one = fgetc(fin);
    if (feof(fin)) {
        //one是所读取文件的一个最后一个字节
//        one>>=8-lastCodesCount;
        for (int i = lastCodesCount - 1; i >= 0; --i) {
            bitCode[i] = (bool) (one % 2);
            one >>= 1;
        }
        for (int j = 0; j < lastCodesCount; ++j) {
            stream.push(bitCode[j]);
        }
    } else {
        for (int i = 7; i >= 0; --i) {
            bitCode[i] = (bool) (one % 2);
            one >>= 1;
        }
        for (int j = 0; j < 8; ++j) {
            stream.push(bitCode[j]);
        }
    }
}



