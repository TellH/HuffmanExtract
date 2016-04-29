//
// Created by tlh on 2016/4/29.
//

#ifndef HUFFMAN_BITSTREAM_H
#define HUFFMAN_BITSTREAM_H

#include <iostream>
#include <queue>

using namespace std;

class BitStream {
private:
    queue<bool> stream;
    FILE *fin;
    int lastCodesCount;

    void _getNewByte();

public:
    BitStream(FILE *fin, int lastCodesCount) : fin(fin), lastCodesCount(lastCodesCount) { }

    bool getBit(bool &data);
};


#endif //HUFFMAN_BITSTREAM_H
