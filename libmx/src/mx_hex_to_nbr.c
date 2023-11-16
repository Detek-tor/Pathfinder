#include "libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
	unsigned long stat = 1;
	unsigned long res = 0;
	if (!hex) return 0;
	int i = 0;
	int count = 0;
	while (hex[i] != '\0') {
		count++;
		i++;
	}
	i = 0;
	for (i = count-1;i>=0; i--) {
		if (mx_isdigit(hex[i])) {
			res += (hex[i] - 48) * stat;
			stat*=16;
		}
		else if (mx_isupper(hex[i])) {
			res += (hex[i] - 55) * stat;
			stat*=16;
		}
		else if (mx_islower(hex[i])) {
			res += (hex[i] - 87)* stat;
			stat*=16;
		}
	}
	return res;
}
