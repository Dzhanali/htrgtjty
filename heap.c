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

int main()
{
    FILE* f1 = fopen("inputheap.txt", "r");
    FILE* f2 = fopen("outputheap.txt", "w");
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
        for(int ind = 0; ind < m; ind++)
        {
            for(int j = (m + 1) / 2 - 1 - ind / 2; j >= 0; j--)
            {
                if(2 * j + 2 <= m - 1 - ind)
                {
                    if(arr[j] < arr[2*j + 2])
                    {
                        swap(&arr[j], &arr[2 * j + 2]);
                    }
                }
                if(2 * j + 1 <= m - 1 - ind)
                {
                    if(arr[j] < arr[2 * j + 1])
                    {
                        swap(&arr[j], &arr[2 * j + 1]);
                    }
                }
                
            }
            swap(&arr[0], &arr[m - 1 - ind]);
        }
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