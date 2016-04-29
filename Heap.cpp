//
// Created by tlh on 2016/4/27.
//

#include "Heap.h"

Heap::Heap(int n, HuffmanTreeNode *h[]) {
    size = n;
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

HuffmanTreeNode **MinHeap::rankFromMax2Min() {
    HuffmanTreeNode **copyHeap = new HuffmanTreeNode *[size + 1];//之所以+1，是因为数组下标0用不到
    for (int i = 1; i <= size; i++) {
        copyHeap[i] = h[i];
    }
    int j = size;
    while (j > 1) {
        _swap(copyHeap, 1, j);
        j--;
        _swiftDown(h, 1, size);
    }
    return copyHeap;
}

HuffmanTreeNode *MinHeap::getTopnMax(int n) {
    HuffmanTreeNode **copyHeap = new HuffmanTreeNode *[n + 1];
    //可任取堆中的n个元素，将副本堆调整成最小堆
    for (int i = 1; i <= n; i++) {
        copyHeap[i] = h[i];
    }
    for (int i = n / 2; i >= 1; i--) {
        _swiftDown(copyHeap, i, n);
    }
    //将父堆中的剩下size-n个元素依次跟副本堆的对顶比较,比较完后副本堆就是前n个最大的元素,对顶就是第n大的元素
    for (int i = n + 1; i <= size; i++) {
        if (h[i] <= copyHeap[1])
            continue;
        else {
            copyHeap[1] = h[i];
            _swiftDown(copyHeap, 1, n);
        }
    }
    return copyHeap[1];
}


