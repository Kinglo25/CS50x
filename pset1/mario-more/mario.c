#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int i;
    int j;
    int k;
    int height = -1;
    int check;

    // prompt the user for a height
    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0 || height > 8);
    i = 1;
    // loop to create the pyramid
    do
    {
        j = 0;
        while (j < height - i)
        {
            printf(" ");
            j++;
        }
        k = 0;
        while (k < i)
        {
            printf("#");
            k++;
        }
        printf("  ");
        while(k--)
        {
            printf("#");
        }
        printf("\n");
        i++;
    }
    while (i <= height);
    return (0);
}