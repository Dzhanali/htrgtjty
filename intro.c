#include<stdio.h>
#include <stdlib.h>
#include <math.h>
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

void quicksort(int* arr, int low, int high, int dep)
{
    if(low >= high)
    {
        return;
    }
    if(dep <= 0){
        for(int ind = low; ind < high; ind++)
        {
            for(int j = (high + 1) / 2 - 1 - ind / 2; j >= 0; j--)
            {
                if(2 * j + 2 <= high - 1 - ind)
                {
                    if(arr[j] < arr[2*j + 2])
                    {
                        swap(&arr[j], &arr[2 * j + 2]);
                    }
                }
                if(2 * j + 1 <= high - 1 - ind)
                {
                    if(arr[j] < arr[2 * j + 1])
                    {
                        swap(&arr[j], &arr[2 * j + 1]);
                    }
                }
                
            }
            swap(&arr[0], &arr[high - 1 - ind]);
        }
    }
    int p = arr[(low + high)/2];
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
    quicksort(arr, low, j, dep - 1);
    quicksort(arr, j + 1, high, dep - 1);
}

int main()
{
    FILE* f1 = fopen("inputintrosort.txt", "r");
    FILE* f2 = fopen("outputintrosort.txt", "w");
    int n = 0, m = 0, dep = 0;
    double start = 0, averT = 0;
    fscanf(f1, "%d", &n);
    int* arr = malloc(sizeof(int));
    for(int i = 0; i < n; i++)
    {
        fscanf(f1, "%d", &m);
        dep = (int)floor(2 * log(m));
        free(arr);
        arr = malloc(sizeof(int) * m);
        for(int j = 0; j < m; j++)
        {
            fscanf(f1, "%d", &arr[j]);
        }
        start = timing();

        quicksort(arr, 0, m - 1, dep);

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