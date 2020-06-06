#ifndef SORT_ALGORITHMS_C_ARRAY_H
#define SORT_ALGORITHMS_C_ARRAY_H

#include "c_sort_array.h"
#include <functional>

template<typename T>
class CArray : public CSortArray<T> {
private:
    using PartitionType = std::function<int(int, int)>;

    unsigned long long _number_of_swaps = 0;
    unsigned long long _number_of_comparisons = 0;

    /**
     * Method creates max heap
     * @param n - size of current processed array
     * @param i - current tree root
     */
    void _heapify(int n, int i);

    int _lomuto_partition(int start_index, int end_index);

    int _hoare_partition(int start_index, int end_index);

    /**
     * Method processes quick sort by using specified PartitionType
     * @param start_index - start index of current array
     * @param end_index - exd index of current array
     * @param partitioning - data partitioning method
     */
    void _quick_sort(int start_index, int end_index, PartitionType partitioning);

public:
    CArray();

    CArray(int size);

    CArray(int size, std::initializer_list<T> values);

    CArray(const CArray<T> &ct);

    CArray(CArray &&) = delete;

    CArray &operator=(const CArray &) = delete;

    CArray &&operator=(CArray &&) = delete;

    ~CArray() = default;

    /**
     * Method implements cocktail sort
     */
    void cocktail_shaker_sort();

    /**
     * Quick sort wrapper
     * @param partition_type - typ of data partitioning (l - for lomuto, any other value for hoare)
     */
    void quick_sort(char partition_type = 'l');

    /**
     * Heap sort wrapper
     */
    void heap_sort();

    /**
     * Method returns number of swaps makes by sort algorithm
     * @return - number of swaps
     */
    inline unsigned long long get_swaps() const { return _number_of_swaps; }

    /**
     * Method returns number of comparisons makes by sort algorithm
     * @return - number of comparisons
     */
    inline unsigned long long get_comparisons() const { return _number_of_comparisons; }
};

template<typename T>
CArray<T>::CArray() : CSortArray<T>() {}

template<typename T>
CArray<T>::CArray(int size) : CSortArray<T>(size) {}

template<typename T>
CArray<T>::CArray(int size, std::initializer_list<T> values) : CSortArray<T>(size, values) {}

template<typename T>
CArray<T>::CArray(const CArray &ct) : CSortArray<T>(ct) {}

template<typename T>
void CArray<T>::cocktail_shaker_sort() {
    bool swapped;

    _number_of_swaps = 0;
    _number_of_comparisons = 0;

    int start_index = 0;
    int end_index = CSortArray<T>::get_size() - 1;

    do {
        swapped = false;

        for (int i = start_index; i < end_index; ++i) {
            _number_of_comparisons++;
            if (CSortArray<T>::_value_array[i] > CSortArray<T>::_value_array[i + 1]) {
                std::swap(CSortArray<T>::_value_array[i], CSortArray<T>::_value_array[i + 1]);
                _number_of_swaps++;
                swapped = true;
            }
        }

        if (!swapped)
            break;
        else {
            swapped = false;
            --end_index;
        }

        for (int i = end_index - 1; i >= start_index; --i) {
            _number_of_comparisons++;
            if (CSortArray<T>::_value_array[i] > CSortArray<T>::_value_array[i + 1]) {
                std::swap(CSortArray<T>::_value_array[i], CSortArray<T>::_value_array[i + 1]);
                _number_of_swaps++;
                swapped = true;
            }
        }

        ++start_index;
    } while (swapped);
}

template<typename T>
int CArray<T>::_lomuto_partition(int start_index, int end_index) {
    int pivot_element = CSortArray<T>::_value_array[end_index];

    int tmp = start_index;

    for (std::size_t i = start_index; i <= end_index; ++i) {
        _number_of_comparisons++;
        if (CSortArray<T>::_value_array[i] < pivot_element) {
            std::swap(CSortArray<T>::_value_array[i], CSortArray<T>::_value_array[tmp]);
            _number_of_swaps++;
            ++tmp;
        }
    }

    std::swap(CSortArray<T>::_value_array[tmp], CSortArray<T>::_value_array[end_index]);
    _number_of_swaps++;
    return tmp;
}

template<typename T>
int CArray<T>::_hoare_partition(int start_index, int end_index) {

    int pivot_element = CSortArray<T>::_value_array[start_index];
    int i = start_index - 1;
    int j = end_index + 1;

    while (1) {
        do {
            i++;
            _number_of_comparisons++;
        } while (CSortArray<T>::_value_array[i] < pivot_element);

        do {
            j--;
            _number_of_comparisons++;
        } while (CSortArray<T>::_value_array[j] > pivot_element);

        if (i >= j)
            return j;

        std::swap(CSortArray<T>::_value_array[i], CSortArray<T>::_value_array[j]);
        _number_of_swaps++;
    }
}

template<typename T>
void CArray<T>::_quick_sort(int start_index, int end_index, PartitionType partitioning) {
    if (start_index >= end_index)
        return;

    int partition_index = partitioning(start_index, end_index);

    _quick_sort(start_index, partition_index - 1, partitioning);
    _quick_sort(partition_index + 1, end_index, partitioning);

}

template<typename T>
void CArray<T>::quick_sort(char partition_type) {
    _number_of_swaps = 0;
    _number_of_comparisons = 0;
    int end_index = CSortArray<T>::get_size() - 1;

    if (partition_type == 'l') {
        PartitionType p_type = [ct = this](int start, int end) { return ct->_lomuto_partition(start, end); };
        _quick_sort(0, end_index, p_type);
    } else {
        PartitionType p_type = [ct = this](int start, int end) { return ct->_hoare_partition(start, end); };
        _quick_sort(0, end_index, p_type);
    }
}

template<typename T>
void CArray<T>::heap_sort() {
    _number_of_comparisons = 0;
    _number_of_swaps = 0;

    int array_size = CSortArray<T>::get_size() - 1;

    // Build heap
    for (int i = array_size / 2; i >= 0; i--) {
        _heapify(array_size, i);
    }

    // Extract root of the current heap by moving it on the "end" of the heap
    for (int i = array_size; i > 0; i--) {
        // Replaces root with "end" of the heap
        std::swap(CSortArray<T>::_value_array[0], CSortArray<T>::_value_array[i]);
        _number_of_swaps++;
        _heapify(i, 0);
    }
}

template<typename T>
void CArray<T>::_heapify(int n, int i) {
    // Current root
    int largest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (left < n and CSortArray<T>::_value_array[left] > CSortArray<T>::_value_array[largest]) {
        largest = left;
    }

    if (right < n and CSortArray<T>::_value_array[right] > CSortArray<T>::_value_array[largest]) {
        largest = right;
    }

    _number_of_comparisons += 2;

    // If left or right node is greater than root, process a swap
    if (largest != i) {
        std::swap(CSortArray<T>::_value_array[i], CSortArray<T>::_value_array[largest]);
        _number_of_swaps++;
        _heapify(n, largest);
    }
}

#endif //SORT_ALGORITHMS_C_ARRAY_H
