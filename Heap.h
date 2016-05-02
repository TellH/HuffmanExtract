//
// Created by tlh on 2016/4/27.
//

#ifndef HUFFMAN_HEAP_H
#define HUFFMAN_HEAP_H


#include "HuffmanTree.h"

class Heap {
protected:
    int contain;
    //堆的容量
    int size;
    //堆中实时存放元素的数目多少，是逻辑数目
    HuffmanTreeNode **h;

    //值交换
    void _swap(HuffmanTreeNode *h[], int a, int b) {
        HuffmanTreeNode *t = h[a];
        h[a] = h[b];
        h[b] = t;
    }

    void _enlarge(HuffmanTreeNode *h[], int n);

public:
    //构造一个空堆，可通过push方法往堆中添加元素
    Heap() {
        size = 0;
        contain = 16;
        h = new HuffmanTreeNode *[contain + 1];
    }

    //直接传过来一个乱堆，做好堆的初始化工作，具体的调整操作由子类来做
    Heap(int n, HuffmanTreeNode *h[]);

    HuffmanTreeNode *getTop() { return h[1]; }
    //~Heap(); /*堆的构造函数就不写了，具体的析构操作由HuffmanTree类来做比较合理。不知道为啥？来求我告诉你呀*/
};

class MinHeap : public Heap {
public:
    MinHeap();

    MinHeap(int n, HuffmanTreeNode *h[]) : Heap(n, h) { _createTree(); };

    //~MinHeap();/*析构函数暂且不写*/
    //往堆中添加元素
    void push(HuffmanTreeNode &node);

    //弹出堆中的TOP元素
    HuffmanTreeNode *pop();

private:
    //向下调整
    void _swiftDown(HuffmanTreeNode *h[], int i, int &size);

    //向上调整
    void _swiftUp(HuffmanTreeNode *h[], int i);

    void _createTree();
};

#endif //HUFFMAN_HEAP_H
