//
// Created by tlh on 2016/4/27.
//

#ifndef HUFFMAN_HUFFMANTREE_H
#define HUFFMAN_HUFFMANTREE_H

#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct HuffmanTreeNode {
    int weight;
    int data;
    HuffmanTreeNode *left;
    HuffmanTreeNode *right;
    HuffmanTreeNode *parent;

    HuffmanTreeNode() { }

    HuffmanTreeNode(int w, int a) : weight(w), data(a), left(NULL), right(NULL), parent(NULL) { }

    HuffmanTreeNode(int d) : weight(d), data('#'), left(NULL), right(NULL), parent(NULL) { }

    HuffmanTreeNode(int d, HuffmanTreeNode *left, HuffmanTreeNode *right, HuffmanTreeNode *parent)
            : weight(d), left(left), right(right), parent(parent) { }

    bool operator>(HuffmanTreeNode &R) { return weight > R.weight; }

    bool operator>=(HuffmanTreeNode &R) { return weight >= R.weight; }

    bool operator<(HuffmanTreeNode &R) { return weight < R.weight; }

    bool operator<=(HuffmanTreeNode &R) { return weight <= R.weight; }

    bool isLeaf() {
        return left == NULL && right == NULL;
    }
};

class HuffmanTree {
public:
    HuffmanTree(HuffmanTreeNode **h, int n);

    HuffmanTreeNode *getRoot() { return root; }

    string *decode(char *code[], int n);

    void buildCodeBook();

    static void encode(FILE *fin, FILE *fout);

    ~HuffmanTree();

    //编码表
    map<int, string> codeBook;
private:
    HuffmanTreeNode *root;

    int leafCount;

    void mergeTree(HuffmanTreeNode &lchildTree, HuffmanTreeNode *parent, HuffmanTreeNode &rchildTree);

    void _Reverse(string &str);

    void _deleteTree(HuffmanTreeNode *p);

    void buildCode(HuffmanTreeNode node, string s);

    void writeCode(vector<int> binaryData, FILE *fout);

};

#endif //HUFFMAN_HUFFMANTREE_H