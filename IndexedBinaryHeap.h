#pragma once

#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <utility>

template <typename KeyT, typename ValueT>
class IndexedBinaryHeap {
public:
    // 构造函数
    IndexedBinaryHeap() = default;
    
    // 移动构造函数
    IndexedBinaryHeap(IndexedBinaryHeap&&) = default;
    
    // 移动赋值运算符
    IndexedBinaryHeap& operator=(IndexedBinaryHeap&&) = default;
    
    // 禁用拷贝构造和拷贝赋值
    IndexedBinaryHeap(const IndexedBinaryHeap&) = delete;
    IndexedBinaryHeap& operator=(const IndexedBinaryHeap&) = delete;

    // 添加元素
    int Push(const ValueT& elem) {
        m_value.push_back(elem);
        m_keyIndex[elem.key] = static_cast<int>(m_value.size() - 1);
        return FixUp(elem.key, m_value.size() - 1);
    }

    // 添加元素（移动语义版本）
    int Push(ValueT&& elem) {
        m_value.push_back(std::move(elem));
        m_keyIndex[m_value.back().key] = static_cast<int>(m_value.size() - 1);
        return FixUp(m_value.back().key, m_value.size() - 1);
    }

    // 判断堆是否为空
    bool Empty() const noexcept {
        return m_value.empty();
    }

    // 判断键是否存在
    bool Exist(const KeyT& key) const noexcept {
        return m_keyIndex.find(key) != m_keyIndex.end();
    }

    // 获取指定键对应的值
    const ValueT& Get(const KeyT& key) const {
        auto it = m_keyIndex.find(key);
        if (it != m_keyIndex.end()) {
            return m_value[it->second];
        }
        throw std::runtime_error("Key not found");
    }

    // 弹出堆顶元素
    ValueT Pop() {
        if (Empty()) {
            throw std::runtime_error("Empty heap");
        }

        ValueT v = std::move(m_value.front());
        if (m_value.size() > 1) {
            m_value.front() = std::move(m_value.back());
            m_keyIndex[m_value.front().key] = 0;
        }
        m_value.pop_back();
        m_keyIndex.erase(v.key);

        if (!Empty()) {
            FixDown(m_value.front().key, 0);
        }

        return v;
    }

    // 更新指定键的优先级
    int Update(const KeyT& key) {
        auto it = m_keyIndex.find(key);
        if (it == m_keyIndex.end()) {
            return -1;
        }
        
        int idx = it->second;
        int f = (idx + 1) / 2 - 1;
        
        if (f >= 0 && m_value[idx] < m_value[f]) {
            return FixUp(key, idx);
        }
        return FixDown(key, idx);
    }

    // 清空堆
    void Clear() noexcept {
        m_value.clear();
        m_keyIndex.clear();
    }

    // 获取堆大小
    size_t Size() const noexcept {
        return m_value.size();
    }

    // 获取堆顶元素
    const ValueT& Top() const {
        if (Empty()) {
            throw std::runtime_error("Empty heap");
        }
        return m_value.front();
    }

private:
    std::vector<ValueT> m_value;
    std::unordered_map<KeyT, int> m_keyIndex;

    int FixDown(const KeyT& key, int idx) {
        const int size = static_cast<int>(m_value.size());
        int f = idx;
        int k = 0;
        
        while ((k = (f * 2) + 1) < size) {
            if (k < size - 1 && m_value[k + 1] < m_value[k]) {
                ++k;
            }
            
            if (m_value[f] <= m_value[k]) {
                break;
            }

            std::swap(m_keyIndex[m_value[f].key], m_keyIndex[m_value[k].key]);
            std::swap(m_value[f], m_value[k]);
            f = k;
        }
        return k;
    }

    int FixUp(const KeyT& key, int idx) {
        int c = idx;
        int f;
        
        while (c > 0 && (f = (c + 1) / 2 - 1) >= 0) {
            if (m_value[f] <= m_value[c]) {
                break;
            }

            std::swap(m_keyIndex[m_value[f].key], m_keyIndex[m_value[c].key]);
            std::swap(m_value[f], m_value[c]);
            c = f;
        }
        return f;
    }
};