#include "libmx.h"

void mx_print_unicode(wchar_t c) {
	char bt[4];

	if (c<0x80)
	{
		bt[0] = (c >> 0 & 0x7F) | 0x00;
		write(1, &bt, 1);
	}
	else if (c<0x0800)
	{
		bt[0] = (c >> 6 & 0x1F) | 0xC0;
		bt[1] = (c >> 0 & 0x3F) | 0x80;
		write(1, &bt, 2);
	}
	else if (c<0x010000)
	{
		bt[0] = (c >> 12 & 0x0F) | 0xE0;
		bt[1] = (c >> 6 & 0x3F) | 0x80;
		bt[2] = (c >> 0 & 0x3F) | 0x80;
		write(1, &bt, 3);
	}
	else
	{
		bt[0] = (c >> 18 & 0x07) | 0xF0;
		bt[1] = (c >> 12 & 0x3F) | 0x80;
		bt[2] = (c >> 6 & 0x3F) | 0x80;
		bt[3] = (c >> 0 & 0x3F) | 0x80;
		write(1, &bt, 4);
	}
}
