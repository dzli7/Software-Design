#include "sort.h"

void ascending_int_sort_whole(int arr[], size_t nelements) {
    int_sort(arr, 0, nelements, int_asc);
}

void ascending_int_sort(int arr[], size_t lo, size_t hi) {
    int_sort(arr, lo, hi, int_asc);
}

void descending_int_sort(int arr[], size_t lo, size_t hi) {
    int_sort(arr, lo, hi, int_desc);
}

void int_sort(int arr[], size_t lo, size_t hi, int_comparator_t compare) {
    for (size_t i = lo; i < hi; i++) {
        int min_idx = i;
        for (int j = i + 1; j < (int) hi; j++) {
            if (compare(arr[j], arr[min_idx]) < 0) {
                min_idx = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

void string_sort(char *arr[], size_t lo, size_t hi, string_comparator_t compare) {
    sort((void**) arr, lo, hi, (comparator_t) compare);
}

void sort(void *arr[], size_t lo, size_t hi, comparator_t compare) {
    for (int i = (int) lo; i < (int) hi; i++) {
        int min_idx = i;
        for (int j = i + 1; j < (int) hi; j++) {
            if (compare(arr[j], arr[min_idx]) < 0) {
                min_idx = j;
            }
        }
        void *temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}
