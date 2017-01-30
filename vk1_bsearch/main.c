#include <stdio.h>
#include <assert.h>

int bsearch(int* arr, int arr_sz, int x)
{
    assert(arr != NULL);
    
    int lo = 0;
    int hi = arr_sz - 1;
    
    int mid;
    while (lo <= hi)
    {
        mid = (lo + hi) / 2;
        if (arr[mid] > x) hi = mid - 1;
        else if (arr[mid] < x) lo = mid + 1;
        else break;
    }
    while (1)
    {
        if (mid == arr_sz) return -1;
        if (arr[mid] > x) return mid;
        ++mid;
    }
}

int main()
{
    const int arrsz = 5;
    int x;

    
    int a1[] = { 1, 2, 5, 8, 8 };
    x = 10;
    printf("X = %d, index: %d\n", x, bsearch(a1, arrsz, x));

    int a2[] = { 8, 8, 8, 8, 10 };
    x = 8;
    printf("X = %d, index: %d\n", x, bsearch(a2, arrsz, x));

    int a3[] = { 1, 2, 5, 8, 10 };
    x = 7;
    printf("X = %d, index: %d\n", x, bsearch(a3, arrsz, x));

    int a4[] = { 1, 2, 5, 8, 10 };
    x = -1;
    printf("X = %d, index: %d\n", x, bsearch(a4, arrsz, x));

    return 0;
}