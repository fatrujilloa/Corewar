#include <stdio.h>

int main()
{
	int a = 65537;
	int b = 128;
	int c;

	c = a & b;
	printf("%d\n", c);
	return (0);
}
