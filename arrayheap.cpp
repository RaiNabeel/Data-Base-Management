#ifndef BHT_H_INCLUDED
#define BHT_H_INCLUDED
#include<iostream>
using namespace std;

template<class T>
class BHT
{
private:
    T* heapArray;
    int capacity;
    int size;

    void resize();
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    BHT();
    ~BHT();

    void insert(T data);
    void deleteRoot();
    T getRoot();

    void display();
};

#endif

#include<iostream>
using namespace std;
#include "BinaryHeapTree.h"

template<class T>
BHT<T>::BHT() {
    capacity = 10; // Initial capacity
    size = 0;
    heapArray = new T[capacity];
}

template<class T>
BHT<T>::~BHT() {
    delete[] heapArray;
}

template<class T>
void BHT<T>::resize() {
    capacity *= 2;
    T* newHeapArray = new T[capacity];
    for (int i = 0; i < size; ++i) {
        newHeapArray[i] = heapArray[i];
    }
    delete[] heapArray;
    heapArray = newHeapArray;
}

template<class T>
void BHT<T>::heapifyUp(int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && heapArray[index] > heapArray[parent]) {
        swap(heapArray[index], heapArray[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

template<class T>
void BHT<T>::heapifyDown(int index) {
    int leftChild, rightChild, maxChild;
    while (true) {
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
        maxChild = index;

        if (leftChild < size && heapArray[leftChild] > heapArray[maxChild]) {
            maxChild = leftChild;
        }

        if (rightChild < size && heapArray[rightChild] > heapArray[maxChild]) {
            maxChild = rightChild;
        }

        if (maxChild == index) {
            break;
        }

        swap(heapArray[index], heapArray[maxChild]);
        index = maxChild;
    }
}

template<class T>
void BHT<T>::insert(T data) {
    if (size == capacity) {
        resize();
    }

    heapArray[size] = data;
    heapifyUp(size);
    size++;
}

template<class T>
void BHT<T>::deleteRoot() {
    if (size == 0) {
        cerr << "Heap is empty." << endl;
        return;
    }

    heapArray[0] = heapArray[size - 1];
    size--;

    heapifyDown(0);
}

template<class T>
T BHT<T>::getRoot() {
    if (size > 0) {
        return heapArray[0];
    } else {
        cerr << "Heap is empty." << endl;
        exit(EXIT_FAILURE);
    }
}

template<class T>
void BHT<T>::display() {
    for (int i = 0; i < size; ++i) {
        cout << heapArray[i] << " ";
    }
    cout << endl;
}
