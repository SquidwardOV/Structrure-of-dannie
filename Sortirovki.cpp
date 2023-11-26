sorting.h

#pragma once


#include <vector>

class Sorting {
public:
    static std::vector<int> merge_sort(const std::vector<int>& arr);
    static std::vector<int> quick_sort(const std::vector<int>& arr);

private:
    static std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right);
};


sorting.cpp

  #include "sorting.h"

#include <algorithm>

std::vector<int> Sorting::merge_sort(const std::vector<int>& arr) {
    if (arr.size() <= 1) {
        return arr;
    }

    int mid = arr.size() / 2;
    std::vector<int> left_half(arr.begin(), arr.begin() + mid);
    std::vector<int> right_half(arr.begin() + mid, arr.end());

    left_half = merge_sort(left_half);
    right_half = merge_sort(right_half);

    return merge(left_half, right_half);
}

std::vector<int> Sorting::merge(const std::vector<int>& left, const std::vector<int>& right) {
    std::vector<int> result;
    size_t i = 0;
    size_t j = 0;

    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            result.push_back(left[i]);
            i++;
        }
        else {
            result.push_back(right[j]);
            j++;
        }
    }

    result.insert(result.end(), left.begin() + i, left.end());
    result.insert(result.end(), right.begin() + j, right.end());

    return result;
}

std::vector<int> Sorting::quick_sort(const std::vector<int>& arr) {
    if (arr.size() <= 1) {
        return arr;
    }

    int pivot = arr[arr.size() / 2];
    std::vector<int> less, equal, greater;

    for (int value : arr) {
        if (value < pivot) {
            less.push_back(value);
        }
        else if (value == pivot) {
            equal.push_back(value);
        }
        else {
            greater.push_back(value);
        }
    }

    std::vector<int> sorted_less = quick_sort(less);
    std::vector<int> sorted_greater = quick_sort(greater);

    sorted_less.insert(sorted_less.end(), equal.begin(), equal.end());
    sorted_less.insert(sorted_less.end(), sorted_greater.begin(), sorted_greater.end());

    return sorted_less;
}

main.cpp

  #include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <numeric>
#include <algorithm> // Для std::is_sorted
#include "sorting.h"
#include <windows.h>

std::vector<int> generate_random_array(int size) {
    std::vector<int> arr;
    for (int i = 0; i < size; ++i) {
        arr.push_back(rand() % 10000 + 1);
    }
    return arr;
}

void check_sorting(const std::string& sort_type, const std::string& array_type, const std::vector<int>& arr);

void check_sorting_on_array(const std::string& sort_type, const std::string& array_type, const std::vector<int>& arr);

int main() {
    SetConsoleOutputCP(1251);
    srand(time(nullptr));

    const int sizes[] = { 500, 1500, 4500 };

    for (int size : sizes) {
        std::vector<int> array_random = generate_random_array(size);// Случайный массив
        std::vector<int> array_sorted(size);
        std::iota(array_sorted.begin(), array_sorted.end(), 1); // Отсортированный массив
        std::vector<int> array_reverse_sorted(size);
        std::iota(array_reverse_sorted.rbegin(), array_reverse_sorted.rend(), 1); // Обратно отсортированный массив
        std::vector<int> array_partial_sorted = generate_random_array(size);
        std::sort(array_partial_sorted.begin(), array_partial_sorted.begin() + size * 0.67); // Частично отсортированный массив (67% от размера)

        check_sorting("Сортировка слиянием", "Случайный", array_random);
        check_sorting("Сортировка слиянием", "Отсортированный массив", array_sorted);
        check_sorting("Сортировка слиянием", "Обратно отсортированный массив", array_reverse_sorted);
        check_sorting("Сортировка слиянием", "Частично отсортированный массив", array_partial_sorted);

        check_sorting("Быстрая сортировка", "Случайный", array_random);
        check_sorting("Быстрая сортировка", "Отсортированный массив", array_sorted);
        check_sorting("Быстрая сортировка", "Обратно отсортированный массив", array_reverse_sorted);
        check_sorting("Быстрая сортировка", "Частично отсортированный массив", array_partial_sorted);
    }

    return 0;
}

void check_sorting(const std::string& sort_type, const std::string& array_type, const std::vector<int>& arr) {
    check_sorting_on_array(sort_type, array_type, arr);
}

void check_sorting_on_array(const std::string& sort_type, const std::string& array_type, const std::vector<int>& arr) {
    std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
    std::vector<int> sorted_arr;

    if (sort_type == "Сортировка слиянием") {
        sorted_arr = Sorting::merge_sort(arr);
    }
    else if (sort_type == "Быстрая сортировка") {
        sorted_arr = Sorting::quick_sort(arr);
    }

    std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();

    // Calculating time duration in nanoseconds
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();

    bool is_sorted = std::is_sorted(sorted_arr.begin(), sorted_arr.end());

    std::cout << sort_type << " on " << array_type << " Массив (Размер: " << arr.size() << "): ";
    std::cout << (is_sorted ? "Прошло" : "Ошибка") << " (Времени: " << duration << " наносекунд)\n";
}
