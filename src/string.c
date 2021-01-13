#include "string.h"
#include <stddef.h>
size_t strlen(char* str) {
        size_t len = 0;
        while (str[len]) ++len;
        return len;
}
char* strcat(char* str1, char* str2) {
	const size_t base = strlen(str1);
	for (int i = 0; i < strlen(str2); ++i) {
		str1[base + i] = str2[i];
	}
	return str1;
}
char* string_reverse(char* str) {
        size_t len = strlen(str);
        for  (int i = 0; i < len / 2; ++i) {
                char tmp = str[i];
                str[i] = str[len - i - 1];
                str[len - i - 1] = tmp;
        }
	return str;
}
char* itoa(int num, char* str) {
	//K&R implementation
        int i, sign;
        if ((sign = num) < 0) num = -num; //check sign and change if needed
        i = 0;
        do {
                str[i++] = num % 10 + '0';
        }  while ((num /= 10) > 0); //keep going while above zero
        if (sign < 0) str[i++] = '-'; //add sign
        str[i] = '\0'; //add null terminator
	string_reverse(str); //reverse string
	return str;
}
