#include <stdio.h>
#include <stdlib.h>

#include "quick_sort.h"

void insertion_sort(int a[], int n)
{
    int j, p;
    int tmp;

    for(p = 1; p < n; p ++) {
        tmp = a[p];
        for(j = p; j > 0 && a[j - 1] > tmp; j--) {
            a[j] = a[j - 1];
        }
        a[j] = tmp;
    }
}
void swap(int *a, int *b)
{
    int c;

    c = *a;
    *a = *b;
    *b = c;
}
int median3(int a[], int left, int right)
{
    int center = (left + right)/2;

    if(a[left] > a[center]) {
        swap(&a[left], &a[center]);
    }
    if(a[left] > a[right]) {
        swap(&a[left], &a[right]);
    }
    if(a[center] > a[right]) {
        swap(&a[center], &a[right]);
    }

    swap(&a[center], &a[right - 1]);
    return a[right - 1];
}
#define CUTOFF (3)
void q_sort(int a[], int left, int right)
{
    int i, j;
    int pivot;

    if(left + CUTOFF <= right) {
        pivot = median3(a, left, right);
        i = left;
        j = right - 1;
        for(;;) {
            while(a[++i] < pivot){}
            while(a[--j] > pivot){}
            if(i < j) {
                swap(&a[i], &a[j]);
            }
            else {
                break;
            }
        }
        swap(&a[i], &a[right - 1]);
        q_sort(a, left, i - 1);
        q_sort(a, i + 1, right);
    }
    else {
        insertion_sort(a + left, right - left + 1);
    }
}
void quick_sort(int a[], int n)
{
    q_sort(a, 0, n -1);
}
