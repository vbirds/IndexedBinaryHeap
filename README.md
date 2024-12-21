# IndexedBinaryHeap

IndexedBinaryHeap是一个基于索引的二叉堆实现，支持高效的插入、删除和查找操作。

## 项目结构


## 文件说明

- `IndexedBinaryHeap.h`：包含IndexedBinaryHeap类的定义和实现。
- `main.cpp`：包含示例代码，展示如何使用IndexedBinaryHeap类。

## 编译使用说明

直接头文件包含 `IndexedBinaryHeap.h` 


## 示例代码

以下是`main.cpp`中的示例代码，展示了如何使用IndexedBinaryHeap类：

```cpp
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
```

# 类IndexedBinaryHeap
IndexedBinaryHeap类是一个模板类，支持以下操作：

- Push：插入元素。
- Pop：弹出堆顶元素。
- Empty：判断堆是否为空。
- Exist：判断键是否存在。
- Get：获取指定键对应的值。

详细的类定义请参考IndexedBinaryHeap.h