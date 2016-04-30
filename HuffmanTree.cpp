//
// Created by tlh on 2016/4/27.
//

#include <cstring>
#include "HuffmanTree.h"
#include "Heap.h"
#include "BitStream.h"

HuffmanTree::~HuffmanTree() {
    _deleteTree(root);
}

void HuffmanTree::_deleteTree(HuffmanTreeNode *p) {
    if (p != NULL) {
        _deleteTree(p->left);
        _deleteTree(p->right);
        delete p;
    }
}

/**
 * 通过传入HuffmanTreeNode的数组建立哈夫曼树
 */
HuffmanTree::HuffmanTree(HuffmanTreeNode *h[], int n) {
    leafCount = n;
    MinHeap heap(n, h);
    HuffmanTreeNode *n1 = NULL;
    HuffmanTreeNode *n2 = NULL;
    HuffmanTreeNode *parent = NULL;
    for (int i = 0; i < n - 1; i++) {
        n1 = heap.pop();
        n2 = heap.pop();
        parent = new HuffmanTreeNode(n1->weight + n2->weight);
        mergeTree(*n1, parent, *n2);
        heap.push(*parent);
    }
    root = parent;
}

void HuffmanTree::mergeTree(HuffmanTreeNode &lchildTree, HuffmanTreeNode *parent, HuffmanTreeNode &rchildTree) {
    parent->left = &lchildTree;
    parent->right = &rchildTree;
    lchildTree.parent = parent;
    rchildTree.parent = parent;
}


void HuffmanTree::buildCodeBook() {
    buildCode(*root, "");
}

void HuffmanTree::buildCode(HuffmanTreeNode node, string s) {
    if (node.isLeaf()) {
        codeBook.insert(map<int, string>::value_type(node.data, s));
        return;
    }
    buildCode(*node.left, s + '0');
    buildCode(*node.right, s + '1');
}

void HuffmanTree::writeCode(vector<int> binaryData, FILE *fout) {
    if (binaryData.size() == 0) return;
    fpos_t startPos;//记录初始写入的位置
    fgetpos(fout, &startPos);
    //计数，满八位则写入文件；写java惯坏了，c++所有变量一定先要初始化
    long bits = 0;
    int buffer = 0;
    vector<int> codes;
    for (int i = 0; i < binaryData.size(); ++i) {
        string code = codeBook[binaryData.at(i)];
        for (int j = 0; j < code.size(); j++) {
            buffer <<= 1;
            if (code[j] == '1')
                buffer += 1;
            bits++;
            if (bits % 8 == 0) {//满8位，则存储
                //cout << buffer << endl;
                codes.push_back(buffer);
                //fputc(buffer, fout);
                buffer = 0;
            }
        }
    }
    if (bits % 8 == 0) {
        //fsetpos(fout, &startPos);
        fputc(8, fout);
        int lastCodeBitsCount = bits % 8;
        fputc(lastCodeBitsCount, fout);
        for (int i = 0; i < codes.size(); i++){
            fputc(codes.at(i), fout);
        }
        return;
    }
    int lastCodeBitsCount = bits % 8;
    fputc(lastCodeBitsCount, fout);
    for (int i = 0; i < codes.size(); i++){
        fputc(codes.at(i),fout);
    }
    fputc(buffer, fout);
}

void HuffmanTree::encode(FILE *fin, FILE *fout) {
    //统计字节出现的频率
    //一个字节的表示范围是0-255，声明权值数组
    int weight[256];
    if (fin == NULL) {
        cout << "file not found" << endl;
        return;
    }
    //将权值数组初始化
    memset(weight, 0, sizeof(weight));
    int c;
    vector<int> binaryData;
    while (true) {
        c = fgetc(fin);
        if (feof(fin)) break;
        weight[c]++;
        binaryData.push_back(c);
//        cout<<c<<endl;
    }
    fclose(fin);
    int count = 0;
    HuffmanTreeNode **treeNodes = new HuffmanTreeNode *[256 + 1];
    //从i=1开始，方便最小堆的建立
    for (int i = 0; i < 256; i++) {
        if (weight[i] == 0) continue;
        treeNodes[++count] = new HuffmanTreeNode(weight[i], i);
    }
    HuffmanTree tree(treeNodes, count);
    tree.writeWeight(weight, fout);
    tree.buildCodeBook();
    tree.writeCode(binaryData, fout);
    fclose(fout);
}

void HuffmanTree::writeWeight(int *weight, FILE *fout) {
    int weightCopy[256];
    for (int i = 0; i < 256; ++i) {
        weightCopy[i]=weight[i];
    }
    fwrite(&weightCopy, sizeof(weight[0]), 256, fout);
    //for (int i = 0; i < 256; ++i) {
    //   // fputc(weight[i], fout);
    //}
}

HuffmanTree *HuffmanTree::readWeightAndBuildTree(FILE *fin) {
    int count = 0;
    HuffmanTreeNode **treeNodes = new HuffmanTreeNode *[256 + 1];
    int weight[256];
    fread(&weight, sizeof(weight[0]), 256, fin);
    //从i=1开始，方便最小堆的建立
    for (int i = 0; i < 256; i++) {
        //int weight = fgetc(fin);
        if (weight[i] == 0) continue;
        treeNodes[++count] = new HuffmanTreeNode(weight[i], i);
    }
    return new HuffmanTree(treeNodes, count);
}

void HuffmanTree::decode(FILE *fin, FILE *fout) {
    if (fin == NULL) {
        cout << "file not found" << endl;
        return;
    }
    HuffmanTree *tree = readWeightAndBuildTree(fin);
    int lastCodeBitsCount = fgetc(fin);
    BitStream stream(fin, lastCodeBitsCount);
    bool bit;
    HuffmanTreeNode *p = tree->getRoot();
    while (stream.getBit(bit)) {
        if (bit == 0) p = p->left;
        else p = p->right;
        if (p != NULL && p->isLeaf()) {
            fputc(p->data, fout);
            p = tree->getRoot();
        }
    }
    fclose(fin);
    fclose(fout);
}
