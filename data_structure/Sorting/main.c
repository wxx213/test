#include <stdio.h>
#include <stdlib.h>

#include "merge_sort.h"
#include "quick_sort.h"

void shell_sort(int a[], int n)
{
    int i, j, inc;
    int tmp;

    for(inc = n/2; inc > 0; inc /= 2) {
        for(i = inc; i < n; i ++) {
            tmp = a[i];
            for(j = i; j >= inc; j -= inc) {
                if(tmp < a[j - inc]) {
                    a[j] = a[j - inc];
                }
                else {
                    break;
                }
            }
            a[j] = tmp;
        }
    }
}

int main()
{
    int aa[] = {5, 13, 9, 2, 10, 17, 1, 0, 19, 11};
    int i;

    //insertion_sort(aa, 10);
    //shell_sort(aa, 10);
    //merge_sort(aa, 10);
    quick_sort(aa, 10);
    for(i = 0; i < 10; i ++) {
        printf("%d ", aa[i]);
    }
    printf("\n");
    return 0;
}
