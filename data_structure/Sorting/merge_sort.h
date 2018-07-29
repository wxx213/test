#ifndef MERGE_SORT_H
#define MERGE_SORT_H
void merge_sort(int a[], int n);

void merge(int a[], int tmp_array[], int lpos, int rpos, int right_end);
void m_sort(int a[], int tmp_array[], int left, int right);

#endif // MERGE_SORT_H
