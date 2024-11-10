#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For usleep()

#define SIZE 6    // Size of the array
#define DELAY 1000000  // Delay in microseconds for animation (0.1 second)

// Function to clear the console screen
void clearScreen() {
    printf("\033[H\033[J");  // ANSI escape code to clear the screen
}

// Function to print the array with highlighted elements
void printArray(int arr[], int size, int highlight1, int highlight2) {
    for (int i = 0; i < size; i++) {
        if (i == highlight1 || i == highlight2) {
            // Highlight the current elements being sorted in red
            printf("\033[1;31m%d \033[0m", arr[i]);
        } else {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

// Bubble Sort with real-time visualization
void bubbleSortVisualize(int arr[], int size) {
    int swapped;
    for (int i = 0; i < size - 1; i++) {
        swapped = 0;
        for (int j = 0; j < size - i - 1; j++) {
            clearScreen();
            printArray(arr, size, j, j + 1);  // Highlight current elements being compared
            usleep(DELAY);

            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;

                clearScreen();
                printArray(arr, size, j, j + 1);  // Highlight swapped elements
                usleep(DELAY);
            }
        }
        if (!swapped) {
            break;
        }
    }
}

// Insertion Sort with real-time visualization
void insertionSortVisualize(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];

            clearScreen();
            printArray(arr, size, j, j + 1);  // Highlight elements being moved
            usleep(DELAY);

            j--;
        }
        arr[j + 1] = key;

        clearScreen();
        printArray(arr, size, j + 1, i);  // Highlight insertion point
        usleep(DELAY);
    }
}

// Quick Sort helper function for partitioning
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        clearScreen();
        printArray(arr, SIZE, j, high);  // Highlight current element and pivot
        usleep(DELAY);

        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            clearScreen();
            printArray(arr, SIZE, i, j);  // Highlight swapped elements
            usleep(DELAY);
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    clearScreen();
    printArray(arr, SIZE, i + 1, high);  // Highlight final pivot position
    usleep(DELAY);
    return i + 1;
}

// Quick Sort with real-time visualization
void quickSortVisualize(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortVisualize(arr, low, pi - 1);
        quickSortVisualize(arr, pi + 1, high);
    }
}

// Function to copy array
void copyArray(int source[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

int main() {
    int arr[SIZE], originalArr[SIZE];

    // Prompt user to enter the elements of the array
    printf("Enter %d elements for the array:\n", SIZE);
    for (int i = 0; i < SIZE; i++) {
        scanf("%d", &originalArr[i]);
    }

    int choice;
        // Reset array to original state for each sort
        copyArray(originalArr, arr, SIZE);
        
        printf("\nOriginal Array: ");
        printArray(arr, SIZE, -1, -1);  // Print array without highlights
        
        printf("\nChoose a sorting algorithm for visualization:\n");
        printf("1. Bubble Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Quick Sort\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nVisualizing Bubble Sort:\n");
                usleep(1000000);
                bubbleSortVisualize(arr, SIZE);
                break;
            case 2:
                printf("\nVisualizing Insertion Sort:\n");
                usleep(1000000);
                insertionSortVisualize(arr, SIZE);
                break;
            case 3:
                printf("\nVisualizing Quick Sort:\n");
                usleep(1000000);
                quickSortVisualize(arr, 0, SIZE - 1);
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please select between 1 and 4.\n");
        }

        if (choice >= 1 && choice <= 3) {
            printf("\nSorted Array: ");
            printArray(arr, SIZE, -1, -1);  // Print sorted array without highlights
        }

    

    return 0;
}
