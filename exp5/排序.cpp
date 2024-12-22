#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// ∆≈›≈≈–Ú
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ≤Â»Î≈≈–Ú
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// —°‘Ò≈≈–Ú
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

// πÈ≤¢≈≈–Ú
void merge(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge(arr, left, mid);
    merge(arr, mid + 1, right);

    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (i = left, k = 0; i <= right; ++i, ++k) {
        arr[i] = temp[k];
    }
}

void mergeSort(vector<int>& arr) {
    merge(arr, 0, arr.size() - 1);
}

// øÏÀŸ≈≈–Ú
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// øÏÀŸ≈≈–Úµƒ  ≈‰∆˜∫Ø ˝
void quickSortWrapper(vector<int>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}

// ∂—≈≈–Ú
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i >= 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// –‘ƒ‹≤‚ ‘∫Ø ˝
void testSortingAlgorithm(void (*sortFunc)(vector<int>&), const vector<int>& arr, const string& name) {
    vector<int> arrCopy = arr;
    auto start = chrono::high_resolution_clock::now();
    sortFunc(arrCopy);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << name << " took " << duration.count() << " s." << endl;
}

int main() {
    const int SIZE = 500; //  ˝◊È¥Û–°
    vector<int> arr(SIZE);

    // À≥–Ú–Ú¡–
    for (int i = 0; i < SIZE; ++i) arr[i] = i;

    cout << "Testing on Sorted Array:\n";
    testSortingAlgorithm(bubbleSort, arr, "∆≈›≈≈–Ú");
    testSortingAlgorithm(insertionSort, arr, "≤Â»Î≈≈–Ú");
    testSortingAlgorithm(selectionSort, arr, "—°‘Ò≈≈–Ú");
    testSortingAlgorithm(mergeSort, arr, "πÈ≤¢≈≈–Ú");
    testSortingAlgorithm(quickSortWrapper, arr, "øÏÀŸ≈≈–Ú");  //  π”√  ≈‰∆˜
    testSortingAlgorithm(heapSort, arr, "∂—≈≈–Ú");

    // ƒÊ–Ú–Ú¡–
    reverse(arr.begin(), arr.end());

    cout << "\nTesting on Reversed Array:\n";
    testSortingAlgorithm(bubbleSort, arr, "∆≈›≈≈–Ú");
    testSortingAlgorithm(insertionSort, arr, "≤Â»Î≈≈–Ú");
    testSortingAlgorithm(selectionSort, arr, "—°‘Ò≈≈–Ú");
    testSortingAlgorithm(mergeSort, arr, "πÈ≤¢≈≈–Ú");
    testSortingAlgorithm(quickSortWrapper, arr, "øÏÀŸ≈≈–Ú");  //  π”√  ≈‰∆˜
    testSortingAlgorithm(heapSort, arr, "∂—≈≈–Ú");

    // ÀÊª˙–Ú¡–
    random_device rd;
    mt19937 g(rd());
    shuffle(arr.begin(), arr.end(), g);

    cout << "\nTesting on Random Array:\n";
    testSortingAlgorithm(bubbleSort, arr, "∆≈›≈≈–Ú");
    testSortingAlgorithm(insertionSort, arr, "≤Â»Î≈≈–Ú");
    testSortingAlgorithm(selectionSort, arr, "—°‘Ò≈≈–Ú");
    testSortingAlgorithm(mergeSort, arr, "πÈ≤¢≈≈–Ú");
    testSortingAlgorithm(quickSortWrapper, arr, "øÏÀŸ≈≈–Ú");  //  π”√  ≈‰∆˜
    testSortingAlgorithm(heapSort, arr, "∂—≈≈–Ú");

    return 0;
}
