#include "libmx.h"

static int num_length(int number) {
	int len = 0;

	while (number)
	{
		number /= 10;
		len++;
	}
	return len;
}

char *mx_itoa(int number) {

	int len = num_length(number);
	int tmp = number;
	char *res = NULL;

	res = mx_strnew(len);
	if (number == 0)
		return mx_strcpy(res, "0");

	if (number == -2147483648)
		return mx_strcpy(res, "-2147483648");
		
	tmp = number;
	for (int i = 0; i < len; i++)
	{
		if (tmp < 0)
		{
			res[len] = '-';
			tmp = -tmp;
		}
		res[i] = (tmp % 10) + '0';
		tmp /= 10;
	}
	mx_str_reverse(res);
	return res;
}
