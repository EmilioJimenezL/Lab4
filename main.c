#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Funciones de ordenamiento
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    int temp;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void countingSort(int arr[], int n, int exp) {
    int output[n]; // Arreglo de salida
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSort(arr, n, exp);
}

// Funciones auxiliares

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void generateRandomArray(int arr[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1001; // Generar números aleatorios entre 0 y 1000
    }
}

int main() {
    int choice, n;
    char continuar;

    do {
        printf("Ingrese el numero de elementos a ordenar: \n");
        scanf("%d", &n);

        int arr[n], arr_copy[n]; // Array para almacenar los datos a ordenar

        generateRandomArray(arr, n); // Generar un array aleatorio para ordenar

        printf("\nArreglo sin ordenar:\n");
        printArray(arr, n);

        printf("\nSeleccione el metodo de ordenamiento:\n");
        printf("1. Bubble sort\n");
        printf("2. Selection sort\n");
        printf("3. Insertion sort\n");
        printf("4. Merge sort\n");
        printf("5. Quick sort\n");
        printf("6. Radix sort\n");
        scanf("%d", &choice);

        clock_t start, end; // Variables para medir el tiempo de ejecución
        double cpu_time_used;

        // Copiar el arreglo original para preservarlo y comparar tiempos de ordenamiento
        memcpy(arr_copy, arr, n * sizeof(int));

        switch (choice) {
            case 1:
                start = clock();
                bubbleSort(arr_copy, n);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("\nArreglo ordenado usando Bubble sort:\n");
                printArray(arr_copy, n);
                break;
            case 2:
                start = clock();
                selectionSort(arr_copy, n);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("\nArreglo ordenado usando Selection sort:\n");
                printArray(arr_copy, n);
                break;
            case 3:
                start = clock();
                insertionSort(arr_copy, n);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("\nArreglo ordenado usando Insertion sort:\n");
                printArray(arr_copy, n);
                break;
            case 4:
                start = clock();
                mergeSort(arr_copy, 0, n - 1);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("\nArreglo ordenado usando Merge sort:\n");
                printArray(arr_copy, n);
                break;
            case 5:
                start = clock();
                quickSort(arr_copy, 0, n - 1);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("\nArreglo ordenado usando Quick sort:\n");
                printArray(arr_copy, n);
                break;
            case 6:
                start = clock();
                radixSort(arr_copy, n);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("\nArreglo ordenado usando Radix sort:\n");
                printArray(arr_copy, n);
                break;
            default:
                printf("\nOpcion no valida.\n");
                return 1;
        }

        printf("\nTiempo de ordenamiento: %f segundos\n", cpu_time_used);

        printf("\nDesea ordenar un nuevo arreglo? (s/n):\n");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    return 0;
}