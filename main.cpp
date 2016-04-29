#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "HuffmanTree.h"

using namespace std;

void encode() {
    FILE *fin = fopen("C:\\Users\\tlh\\ClionProjects\\Huffman\\temp.bmp", "rb");
    FILE *fout = fopen("C:\\Users\\tlh\\ClionProjects\\Huffman\\temp.huf", "wb");
    HuffmanTree::encode(fin, fout);
}

void decode() {
    FILE *fin = fopen("C:\\Users\\tlh\\ClionProjects\\Huffman\\temp.huf", "rb");
    FILE *fout = fopen("C:\\Users\\tlh\\ClionProjects\\Huffman\\temp.bmp", "wb");
    HuffmanTree::decode(fin,fout);
}

void readFile() {
    FILE *fin = fopen("C:\\Users\\tlh\\ClionProjects\\Huffman\\temp.huf", "rb");
    if (fin == NULL) {
        cout << "无法打开文件" << endl;
        return;
    }
    int c;
    while (true) {
        c = fgetc(fin);
        cout << c << endl;
        if (feof(fin)) break;
    }
    fclose(fin);
}

int main() {
//    encode();
    decode();
    return 0;
}