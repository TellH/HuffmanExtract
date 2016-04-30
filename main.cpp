#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "HuffmanTree.h"

using namespace std;

void encode(char src[], char dst[]) {
    //�Զ��������ķ�ʽ��IO��
    FILE *fin = fopen(src, "rb");
    FILE *fout = fopen(dst, "wb");
    HuffmanTree::encode(fin, fout);
}

void decode(char src[], char dst[]) {
    //�Զ��������ķ�ʽ��IO��
    FILE *fin = fopen(src, "rb");
    FILE *fout = fopen(dst, "wb");
    HuffmanTree::decode(fin, fout);
}

bool help(int &op) {
    system("cls");
    cout<<"|����������ʵ���ļ�ѹ��|"<<endl;
    cout<<"����: "<<endl;
    cout<<"_________________________________ "<<endl;
    cout<<"|����1��ѹ���ļ�|"<<endl;
    cout<<"|����2����ѹ�ļ�|"<<endl;
    cout<<"|����0���˳�     |"<<endl;
    cout<<"--------------------------------- "<<endl;
    do {
        cout<<"��ѡ��"<<endl;
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
                printf("�������ѹ���ļ�·����");
                scanf("%s", srcFile);
                printf("������ѹ���ļ�·����");
                scanf("%s", dstFile);
                encode(srcFile, dstFile);
                cout << "ѹ����ɣ�" << endl;
                break;
            case 2:
                cout<<"���������ѹ�ļ�·����"<<endl;
                scanf("%s", srcFile);
                cout<<"�������ѹ���ļ�·����"<<endl;
                scanf("%s", dstFile);
                decode(srcFile, dstFile);
                cout << "��ѹ��ɣ�" << endl;
                break;
        }
        cout<<"�����������..."<<endl;
        getchar();
        getchar();
    }
    return 0;
}