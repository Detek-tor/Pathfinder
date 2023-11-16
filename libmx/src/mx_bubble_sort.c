#include "libmx.h"

int mx_bubble_sort(char **arr, int size) {
	char *status;
	int res = 0;
	for (int j = 0; j<size; j++) {
		for (int i = j+1; i<size; i++) {
			if (mx_strcmp(arr[j], arr[i])>0) {
				status = arr[j];
				arr[j] = arr[i];
				arr[i] = status;
				res++;
			}
		}
	}
	return res;
}
