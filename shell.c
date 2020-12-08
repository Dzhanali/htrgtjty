#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct list
{
    int val;
    struct list *next;
};

struct list *add(struct list *head, int val)
{
    struct list *new = (struct list*)malloc(sizeof(struct list));
    new->val = val;
    struct list *temp = head;
    new->next = temp;
    return new;
}

void freeList(struct list *head){
    struct list *temp = head;
    while(head != NULL){
        head = head->next;
        free(temp);
        temp = head;
    }
}

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
    FILE* f1 = fopen("inputshell.txt", "r");
    FILE* f2 = fopen("outputshell.txt", "w");
    int n = 0, m = 0, d = 0, k = 0, ind = 0, tmp = 0;
    double start = 0, averT = 0;
    fscanf(f1, "%d", &n);
    int* arr = malloc(sizeof(int));
    struct list* lstofds = NULL;
    for(int i = 0; i < n; i++)
    {
        lstofds = NULL;
        fscanf(f1, "%d", &m);
        free(arr);
        arr = malloc(sizeof(int) * m);
        for(int j = 0; j < m; j++)
        {
            fscanf(f1, "%d", &arr[j]);
        }
        d = 0;
        k = 0;
        start = timing();
        while(1){

            if(k % 2 == 0)
            {
                d = 9 * (int)pow(2, k) - 9 * (int)pow(2, k / 2) + 1;
            }
            else
            {
                d = 8 * (int)pow(2, k) - 6 * (int)pow(2, (k + 1) / 2) + 1;
            }
            if(3 * d >= m)
            {
                break;
            }
            lstofds = add(lstofds, d);
            k++;
        }
        ind = 0;
        while(lstofds != NULL)
        {
            for(int j = 0; j < m - lstofds->val; j++)
            {
                ind = j;
                while(ind >= 0 && arr[ind] > arr[ind + lstofds->val])
                {
                    swap(&arr[ind], &arr[ind + lstofds->val]);
                    ind -= lstofds->val;
                }
            }
            lstofds = lstofds->next;
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
    freeList(lstofds);
    free(arr);
    fclose(f1);
    fclose(f2);
    return 0;
}