#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr){
	if (!nbr || nbr<1) return 0;
	int size = 1;
	char *res = mx_strnew(size);
	res[0] = '\0';

	while(nbr != 0){
	    unsigned long ti = nbr % 16;
	    if(ti < 10)
	        ti += '0';
        else
            ti += 'a' - 10;
        char *s = mx_strnew(size++);
        s[0] = ti;

        for(int i = 0; i < size - 1; i++)
            s[i + 1] = res[i];
        res = s;
        nbr /= 16;
	}

	return res;
}
