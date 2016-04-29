//
// Created by tlh on 2016/4/27.
//

#include <cstring>
#include "HuffmanTree.h"
#include "Heap.h"

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

void HuffmanTree::_Reverse(string &str) {
    int len = str.length();
    char tchar;
    for (int i = 0; i < len / 2; i++) {
        tchar = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tchar;
    }
}

string *HuffmanTree::decode(char *code[], int n) {
    if (root == NULL) {
        cout << "Are you kidding me?" << endl;
    }
    string *content = new string[n];
    for (int i = 0; i < n; i++) {
        char *codeNum = code[i];
        int j = 0;
        HuffmanTreeNode *p = root;
        while (codeNum[j] != '\0') {
            if (p == NULL) {
                cout << "你输入的编码有误！没有此编码" << endl;
                return NULL;
            }
            if (codeNum[j] == '0') {
                p = p->left;
            }
            else if (codeNum[j] == '1') {
                p = p->right;
            }
            else {
                cout << "你输入的编码有误！" << endl;
                return NULL;
            }
            j++;
        }
        content[i] = p->data;
    }
    return content;
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
    //计数，满八位则写入文件；写java惯坏了，c++所有变量一定先要初始化
    long bits = 0;
    int buffer = 0;
    for (int i = 0; i < binaryData.size(); ++i) {
        string code = codeBook[binaryData.at(i)];
        for (int j = 0; j < code.size(); j++) {
            buffer <<= 1;
            if (code[j] == '1')
                buffer += 1;
            bits++;
            if (bits % 8 == 0) {//满8位，则存储
//                cout << buffer << endl;
                fputc(buffer, fout);
                buffer = 0;
            }
        }
    }
    if (bits % 8 == 0){
        fseek(fout, 0, SEEK_SET);
        fputc(8, fout);
        return;
    }
    int lastCodeBitsCount = bits % 8;
//    buffer <<= 8 - lastCodeBitsCount;
    fputc(buffer, fout);
    //在文件开头写入最后一个字节包含的bit数
    fseek(fout, 0, SEEK_SET);
    fputc(lastCodeBitsCount, fout);
}

void HuffmanTree::encode(FILE *fin, FILE *fout) {
    int weight[256];//一个字节出现的频率
    if (fin == NULL) {
        cout << "无法打开文件" << endl;
        return;
    }
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
    tree.writeWeight(weight,fout);
    tree.buildCodeBook();
    tree.writeCode(binaryData, fout);
    fclose(fout);
}

void HuffmanTree::writeWeight(int *weight, FILE *fout) {
    for (int i = 0; i < 256; ++i) {
        fputc(weight[i], fout);
    }
}

HuffmanTree * HuffmanTree::readWeightAndBuildTree(FILE *fin) {
    int count = 0;
    HuffmanTreeNode **treeNodes = new HuffmanTreeNode *[256 + 1];
    //从i=1开始，方便最小堆的建立
    for (int i = 0; i < 256; i++) {
        int weight=fgetc(fin);
        if (weight == 0) continue;
        treeNodes[++count] = new HuffmanTreeNode(weight, i);
    }
    return new HuffmanTree(treeNodes,count);
}













