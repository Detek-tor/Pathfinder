#include "libmx.h"

int mx_quicksort(char **arr, int left, int right) {
    if (!arr) return -1;
    int count = 0;

    if (left < right)
    {
        int n = left;
        int j = right;
        char *pivot = arr[(j + n) / 2];

        while (n <= j)
        {
            while (mx_strlen(arr[n]) < mx_strlen(pivot)) n++;
            while (mx_strlen(arr[j]) > mx_strlen(pivot)) j--;

            if (n <= j)
            {
                if (mx_strlen(arr[j]) != mx_strlen(arr[n]))
                {
                    char *temp = arr[n];
                    arr[n] = arr[j];
                    arr[j] = temp;
                    count++;
                }
                j--;
                n++;
            }
        }

        count += mx_quicksort(arr, left, j);
        count += mx_quicksort(arr, n, right);
    }
    return count;
}
