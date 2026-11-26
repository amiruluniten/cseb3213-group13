#ifndef SORTING_H
#define SORTING_H

#include "house.h"

// "Must come first" test, shared by both sorts so rent, distance and ID
// all go through one comparison path. Equal keys return false, which is
// what keeps insertion sort stable: two houses at the same rent keep
// their entry order.
bool comesBefore(House a, House b, int keyType, int order) {
    bool asc = (order == 1);
    if (keyType == 1) {
        if (a.rent == b.rent) {
            return false;
        }
        if (asc) {
            return a.rent < b.rent;
        }
        return a.rent > b.rent;
    }
    if (keyType == 2) {
        if (a.distanceKm == b.distanceKm) {
            return false;
        }
        if (asc) {
            return a.distanceKm < b.distanceKm;
        }
        return a.distanceKm > b.distanceKm;
    }
    if (a.id == b.id) {
        return false;
    }
    if (asc) {
        return a.id < b.id;
    }
    return a.id > b.id;
}

// O(n^2) worst and average, O(n) when the copy is already in order. That
// best case is why it stays a menu option: a nearly-sorted listing set
// costs almost nothing.
void insertionSort(House arr[], int n, int keyType, int order) {
    int i;
    for (i = 1; i < n; i++) {
        House key = arr[i];
        int j = i - 1;
        while (j >= 0 && comesBefore(key, arr[j], keyType, order)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Left half first when the keys are equal, so the sort stays stable.
// Temp holds one merge window. The list itself is never written.
void mergeRange(House arr[], int left, int mid, int right, int keyType, int order) {
    House temp[MAX_HOUSE];
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (comesBefore(arr[j], arr[i], keyType, order)) {
            temp[k] = arr[j];
            j++;
        } else {
            temp[k] = arr[i];
            i++;
        }
        k++;
    }
    while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }
    while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
    }
    for (int t = left; t <= right; t++) {
        arr[t] = temp[t];
    }
}

// O(n log n) best, average and worst. Split in half, sort each half, merge.
void mergeSort(House arr[], int left, int right, int keyType, int order) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, keyType, order);
    mergeSort(arr, mid + 1, right, keyType, order);
    mergeRange(arr, left, mid, right, keyType, order);
}

// Single entry point both menu paths call. Validates the codes coming
// out of the menu, picks the algorithm, sorts arr[0..n-1] in place. No
// allocation, and the linked list itself is never touched.
void sortHouses(House arr[], int n, int method, int keyType, int order) {
    if (n <= 1) {
        return;
    }
    if ((method != 1 && method != 2) || keyType < 1 || keyType > 3 ||
        (order != 1 && order != 2)) {
        cout << "Invalid sort arguments.\n";
        return;
    }
    if (method == 1) {
        insertionSort(arr, n, keyType, order);
    } else {
        mergeSort(arr, 0, n - 1, keyType, order);
    }
}

#endif
