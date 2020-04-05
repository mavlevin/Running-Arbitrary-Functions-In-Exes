#include <stdio.h>

void decode_string(char* s)
{
	while (*s)
	{
		*s = s[0] ^ 0x31 ^ s[1];
		s++;
	}
}

void main()
{
	char s[] = "\x51\x08\x5c\x01\x5c\x02\x13\x18";
	decode_string(s);
	printf("%s\n", s);
	printf("done\n");
}