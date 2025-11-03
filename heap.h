//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }
    // Inserts a new element at the end of the array, calls for upheap, then increments size + 1
    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        data[size] = idx;
        upheap(size,weightArr);
        size++;
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        if (size == 0 ) {
            return -1;
        }
        int rootIndex = data[0];
        data[0] = data[size-1];
        size--;

        downheap(0,weightArr);
        // Replace root with last element, then call downheap()

        return rootIndex; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (pos >0) {
            int parentPos = (pos - 1) / 2;
            if (weightArr[data[pos]] < weightArr[data[parentPos]]) {
                int temp = data[pos];

                data[pos] = data[parentPos];
                data[parentPos] = temp;
                pos = parentPos;
            } else {
                break;
            }

        }
    }

    void downheap(int pos, int weightArr[]) {
        while (true) {
            // TODO: swap parent downward while larger than any child
            int left = pos * 2 + 1;
            int right = pos * 2 + 2;
            int smallest = pos;

            if (left < size && weightArr[data[left]] < weightArr[data[smallest]]) {
                smallest = left;
            }

            if (right < size && weightArr[data[right]] < weightArr[data[smallest]]) {
                smallest = right;
            }
            if (smallest == pos) {
                break;
            }

            int temp = data[pos];
            data[pos] = data[smallest];
            data[smallest] = temp;

            pos = smallest;
        }
    }
};

#endif