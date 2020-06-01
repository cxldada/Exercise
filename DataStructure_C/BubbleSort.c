#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void BubbleSort(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        bool isSort = true;
        for (int j = (size - 1); j > i; --j) {
            if (arr[j] < arr[j - 1]) {
                int t = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = t;
                isSort = false;
            }
        }

        if (isSort)
            break;
    }
}

int main() {
    int arr[5] = {5, 3, 0, 10, 9};
    BubbleSort(arr, 5);

    exit(0);
}
