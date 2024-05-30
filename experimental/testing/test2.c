#include <stdio.h>

void    prueba(int a[2])
{
    a[0] = 1;
    a[1] = 2;
}

int main(void)
{
    int a[2];

    a[0] = -1;
    a[1] = -2;
    printf("%d %d\n", a[0], a[1]);
    printf("Hola mundo!\n");
    prueba(a);
    printf("%d %d\n", a[0], a[1]);
    return (0);
}