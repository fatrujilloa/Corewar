#include <stdio.h>

int main()
{
    unsigned char byte = 164;
    unsigned char a = 128;
    unsigned char b = 64;
    int i = -1;

    printf("BYTE = %d\n",  byte);
    while (++i < 3)
    {
        printf("arg->type[%d]  = %d", i, ((a + b) & byte) >> (6 - 2 * i));
        a = a / 4;
        b = b / 4;
    }
}