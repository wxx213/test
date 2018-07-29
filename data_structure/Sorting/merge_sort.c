#include <stdio.h>
#include <stdlib.h>

#include "merge_sort.h"

void merge(int a[], int tmp_array[], int lpos, int rpos, int right_end)
{
    int i, left_end, num, tmp_pos;

    left_end = rpos - 1;
    tmp_pos = lpos;
    num = right_end - lpos + 1;

    while(lpos <= left_end && rpos <= right_end) {
        if(a[lpos] <= a[rpos]) {
            tmp_array[tmp_pos++] = a[lpos++];
        }
        else {
            tmp_array[tmp_pos++] = a[rpos++];
        }
    }

    while(lpos <= left_end) {
        tmp_array[tmp_pos++] = a[lpos++];
    }
    while(rpos <= right_end) {
        tmp_array[tmp_pos++] = a[rpos++];
    }

    for(i = 0; i < num; i++, right_end--) {
        a[right_end] = tmp_array[right_end];
    }
}
void m_sort(int a[], int tmp_array[], int left, int right)
{
    int center;

    if(left < right) {
        center = (left + right)/2;
        m_sort(a, tmp_array, left, center);
        m_sort(a, tmp_array, center + 1, right);
        merge(a, tmp_array, left, center + 1, right);
    }
}
void merge_sort(int a[], int n)
{
    int *tmp_array;

    tmp_array = malloc(n * sizeof(int));
    if(tmp_array != NULL) {
        m_sort(a, tmp_array, 0, n - 1);
        free(tmp_array);
    }
}
