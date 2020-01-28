#include <stdio.h>

void    ft_strnrev(unsigned char *str, unsigned int size)
{
    unsigned int    i;
    char            tmp;

    i = 0;
    printf("Starting rev\n");
    while (i < size / 2)
    {
        tmp = str[i];
        str[i] = str[size - 1 - i];
        str[size - 1 - i] = tmp;
        i++;
    }
}

unsigned int    ft_str_to_int(unsigned char *str, unsigned int size)
{
    unsigned int    i;
    unsigned int    v;

    v = 0;
    i = 0;
    while (i < size)
    {
        printf("str[%d] = %u\n", i, str[i]);
        v = 256 * v + str[i++];
        printf("v = %u\n", v);
    }
    return (v);
}

int main()
{
    unsigned char a[4];
    unsigned char b[4];
    unsigned char c[4];
    unsigned int    x;
    unsigned int    y;
    unsigned int    z;
    int i;

    a[0] = 255;
    a[1] = 0;
    a[2] = 0;
    a[3] = 0;
    b[0] = 0;
    b[1] = 0;
    b[2] = 0;
    b[3] = 255;
    *(unsigned int*)c = 255;
    printf("a = %u, b = %u, c = %u\n", *(unsigned int*)a, *(unsigned int*)b, *(unsigned int*)c);
    i = -1;
    while (++i < 4)
        printf("a[%d] = %hhu, b[%d] = %hhu, c[%d] = %hhu\n", i, a[i], i, b[i], i, c[i]);
    printf("VALUE of b = %u\n", ft_str_to_int(b, 4));
    ft_strnrev(b, 4);
    printf("VALUE of b after rev = %u\n", ft_str_to_int(b, 4));
    i = -1;
    while (++i < 4)
        printf("b[%d] = %hhu\n", i, b[i]);
    x = 100,
    y = 1000,
    z = x - y;
    printf("\n\n%u, %u\n", -900, z);
    return (0);
}