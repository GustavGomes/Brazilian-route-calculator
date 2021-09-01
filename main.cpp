#include <iostream>
#include <vector>

template <typename T>
struct CustomComparator {
    bool operator()(const T& lhs, const T& rhs) {
        return (lhs < rhs);
    }
};

template <typename T, typename Compare = CustomComparator<T>>
void Merge(std::vector<T>& arr, size_t first_begin, size_t first_end, size_t second_begin,
           size_t second_end, Compare comp = Compare()) {
    std::vector<int> first_array(second_begin - first_begin);
    std::vector<int> second_array(second_end - first_end);

    for (size_t i = 0; i < first_array.size(); i++) {
        first_array[i] = arr[first_begin + i];
    }
    for (size_t j = 0; j < second_array.size(); j++) {
        second_array[j] = arr[first_end + 1 + j];
    }

    size_t i = 0, j = 0;
    size_t k = first_begin;
    while (i < first_array.size() && j < second_array.size()) {
        if (first_array[i] <= second_array[j]) {
            arr[k] = first_array[i];
            i++;
        } else {
            arr[k] = second_array[j];
            j++;
        }
        k++;
    }
    while (i < first_array.size()) {
        arr[k] = first_array[i];
        i++;
        k++;
    }
    while (j < second_array.size()) {
        arr[k] = second_array[j];
        j++;
        k++;
    }
}

template <typename T, typename Compare = CustomComparator<T>>
void MergeSort(std::vector<T>& arr, size_t begin, size_t end, Compare comp = Compare()) {
    if (begin >= end) {
        return;
    }
    size_t m = (begin + end) / 2;
    MergeSort(arr, begin, m);
    MergeSort(arr, m + 1, end);
    Merge(arr, begin, m, m + 1, end);
}

template <typename T, typename Compare = CustomComparator<T>>
void Sort(std::vector<T>& array) {
    MergeSort(array, 0, array.size() - 1);
}

std::vector<int> ReadVector() {
    size_t n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    return arr;
}

void PrintVector(const std::vector<int>& array) {
    for (size_t i = 0; i < array.size(); i++) {
        std::cout << array[i] << ' ';
    }
}

int main() {
    std::vector<int> arr1 = ReadVector();
    Sort(arr1);
    PrintVector(arr1);
    return 0;
}
