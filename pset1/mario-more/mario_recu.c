#include <stdio.h>
#include <cs50.h>

void    create_pyramid(int h)
{
    int i = 0;
    if (h == 0)
        return ;
    create_pyramid(h - 1);
    while (i++ < h)
        printf("#");
    printf("\n");
}

int main(void)
{
    int height = 0;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    create_pyramid(height);
}
