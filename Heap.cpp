//
// Created by tlh on 2016/4/27.
//

#include "Heap.h"

Heap::Heap(int n, HuffmanTreeNode *h[]) {
    size = n;
    contain=16;
    if (contain >= n) { this->h = h; }
    else {
        _enlarge(h, n);
    }
}

void Heap::_enlarge(HuffmanTreeNode *h[], int n) {
    int time = n / 16;
    contain = contain * (time + 1);
    this->h = new HuffmanTreeNode *[contain + 1];
    for (int i = 1; i <= n; i++) {
        this->h[i] = h[i];
    }
}

void MinHeap::_swiftDown(HuffmanTreeNode *h[], int i, int &size) {
    int book;//用于登记将要被交换变量的坐标
    while (i * 2 <= size) {
        book = i;//初始化
        if (*h[i] > *h[i * 2]) {
            //与i的第一个子节点比较
            book = i * 2;
        }
        if (i * 2 + 1 <= size && *h[i * 2 + 1] < *h[book]) {
            //h[book]与i的第二个子节点比较
            book = i * 2 + 1;
        }
        if (book == i) break;
        else {
            _swap(h, book, i);
            i = book;//从book坐标继续向下调整
        }
    }
}

void MinHeap::_swiftUp(HuffmanTreeNode *h[], int i) {
    //跟父节点进行比较
    while (i / 2 >= 1) {
        if (*h[i] < *h[i / 2]) {
            _swap(h, i, i / 2);
            i = i / 2;
        }
        else break;
    }
}

void MinHeap::_createTree() {
    /*
   从最后一个非叶结点开始，依次调整每一个子堆，当每一个子堆都调整好后，整体的大堆也就大功告成了。
   */
    for (int i = size / 2; i >= 1; i--) {
        _swiftDown(h, i, size);
    }
}

HuffmanTreeNode *MinHeap::pop() {
    /*
   删除顶层节点
   */
    _swap(h, 1, size);
    size--; //逻辑删除
    _swiftDown(h, 1, size); //调整维护堆
    return h[size + 1];
}

void MinHeap::push(HuffmanTreeNode &node) {
    size++;
    if (size > contain) {
        _enlarge(h, size - 1);
    }
    h[size] = &node;
    _swiftUp(h, size);
}

