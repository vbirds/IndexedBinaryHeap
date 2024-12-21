#include "IndexedBinaryHeap.h"
#include <iostream>

struct Element {
    int key;
    int value;

    bool operator<=(const Element& other) const {
        return value <= other.value;
    }
    bool operator<(const Element& other) const {
        return value < other.value;
    }

};

int main() {
    IndexedBinaryHeap<int, Element> heap;

    heap.Push({1, 10});
    heap.Push({2, 5});
    heap.Push({3, 20});

    while (!heap.Empty()) {
        Element top = heap.Pop();
        std::cout << "Key: " << top.key << ", Value: " << top.value << std::endl;
    }

    return 0;
}