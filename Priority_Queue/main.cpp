#include <cassert>
#include <iostream>

#include "cpp/heapSort.cpp"
#include "cpp/priority_queue.cpp"

void InsertExtractTest() {
    Priority_Queue<int> pq;

    assert(pq.empty());

    int a[10] = {5, 3, 6, 9, 1, 10, 4, 8, 7, 2};
    for (int i = 0; i < 10; i++)
        pq.insert(a[i]);

    assert(pq.size() == 10);

    for (int i = 10; i >= 1; i--)
        assert(pq.extract_max() == i);

    assert(pq.empty());
}

void ArrayToHeapTest() {
    int* a = new int[10]{5, 3, 6, 9, 1, 10, 4, 8, 7, 2};

    Priority_Queue<int> pq(a, 10);

    assert(pq.size() == 10);

    for (int i = 10; i >= 1; i--)
        assert(pq.extract_max() == i);

    assert(pq.empty());
}

template <typename T = int>
void heapSortPQ(T* a, size_t size) {
    Priority_Queue<T> pq(a, size);

    for (int i = 0; i < size; i++)
        a[i] = pq.extract_max();
}

void HeapSortPQTest() {
    size_t size = 10;
    int* a = new int[size]{5, 3, 6, 9, 1, 10, 4, 8, 7, 2};

    heapSortPQ(a, size);

    for (size_t i = 10; i >= 1; i--)
        assert(a[10 - i] == i);
}

void heapSortTest() {
    size_t size = 10;
    int* a = new int[size]{5, 3, 6, 9, 1, 10, 4, 8, 7, 2};

    // build_heap(a, size);
    heap_sort(a, size);

    for (size_t i = 10; i >= 1; i--)
        assert(a[i - 1] == i);
}

int main() {
    heapSortTest();

    return 0;
}
