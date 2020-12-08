#include<stdio.h>
#include <stdlib.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

double timing()
{
  LARGE_INTEGER freq, val;
  QueryPerformanceFrequency(&freq);
  QueryPerformanceCounter(&val);
  return (double)val.QuadPart / (double)freq.QuadPart;
}

void swap(int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

void quicksort(int* arr, int low, int high)
{
    if(low >= high)
    {
        return;
    }
    int p = arr[(low + high) / 2];
    int i = low - 1;
    int j = high + 1;
    while(1)
    {
        i++;
        while(arr[i] < p)
        {
            i++;
        }
        j--;
        while(arr[j] > p)
        {
            j--;
        }
        if(i >= j)
        {
            break;
        }
        swap(&arr[i], &arr[j]);
    }
    quicksort(arr, low, j);
    quicksort(arr, j + 1, high);
}

int main()
{
    FILE* f1 = fopen("inputquick.txt", "r");
    FILE* f2 = fopen("outputquick.txt", "w");
    int n = 0, m = 0;
    double start = 0, averT = 0;
    fscanf(f1, "%d", &n);
    int* arr = malloc(sizeof(int));
    for(int i = 0; i < n; i++)
    {
        fscanf(f1, "%d", &m);
        free(arr);
        arr = malloc(sizeof(int) * m);
        for(int j = 0; j < m; j++)
        {
            fscanf(f1, "%d", &arr[j]);
        }
        start = timing();

        quicksort(arr, 0, m - 1);

        start = (timing() - start);
        averT += start * 1000;
        for(int j = 0; j < m; j++)
        {
            fprintf(f2, "%d ", arr[j]);
        }
        fprintf(f2, "\n");
        fprintf(f2, "time: %lf\n", start * 1000);
    }
    fprintf(f2, "average time: %lf", averT / (double)n);
    free(arr);
    fclose(f1);
    fclose(f2);
    return 0;
}