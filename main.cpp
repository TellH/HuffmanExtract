#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "HuffmanTree.h"

using namespace std;

void encode(char src[], char dst[]) {
    //以二进制流的方式打开IO流
    FILE *fin = fopen(src, "rb");
    FILE *fout = fopen(dst, "wb");
    HuffmanTree::encode(fin, fout);
}

void decode(char src[], char dst[]) {
    //以二进制流的方式打开IO流
    FILE *fin = fopen(src, "rb");
    FILE *fout = fopen(dst, "wb");
    HuffmanTree::decode(fin, fout);
}

bool help(int &op) {
    system("cls");
    cout<<"|哈夫曼编码实现文件压缩|"<<endl;
    cout<<"功能: "<<endl;
    cout<<"_________________________________ "<<endl;
    cout<<"|输入1：压缩文件|"<<endl;
    cout<<"|输入2、解压文件|"<<endl;
    cout<<"|输入0、退出     |"<<endl;
    cout<<"--------------------------------- "<<endl;
    do {
        cout<<"请选择："<<endl;
        scanf("%d", &op);
    } while (op < 0 || op > 3);
    return op ? true : false;
}

int main() {
    int op;
    char srcFile[100], dstFile[100];
    while (help(op)) {
        switch (op) {
            case 1:
                printf("请输入待压缩文件路径：");
                scanf("%s", srcFile);
                printf("请输入压缩文件路径：");
                scanf("%s", dstFile);
                encode(srcFile, dstFile);
                cout << "压缩完成！" << endl;
                break;
            case 2:
                cout<<"请输入待解压文件路径："<<endl;
                scanf("%s", srcFile);
                cout<<"请输入解压后文件路径："<<endl;
                scanf("%s", dstFile);
                decode(srcFile, dstFile);
                cout << "解压完成！" << endl;
                break;
        }
        cout<<"按任意键继续..."<<endl;
        getchar();
        getchar();
    }
    return 0;
}