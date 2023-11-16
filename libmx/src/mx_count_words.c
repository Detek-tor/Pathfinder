#include "libmx.h"

int mx_count_words(const char *str, char c) {
	int sovp = 0;
	int i = 0;
	bool state = true;
	if (str == NULL)
		return -1;
	else
	{
		while (str[i]) {
			if (str[i] == c) {
				state = true;
			}
			else if (state == true) {
				state = false;
				++sovp;
			}
			++i;
		}
		return sovp;
	}
}
