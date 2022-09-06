#include <stdio.h>
#include <cs50.h>

int get_height(void);

int main(void)
{
    int height = get_height();
    int x = 1;
    int y = height - 1;
    for (int i = 0; i < height; i++)
    {
        for (int w = 0; w < y; w++)
        {
            printf(" ");
        }
        for (int j = 0; j < x; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int g = 0; g < x; g++)
        {
            printf("#");
        }
        printf("\n");
        x ++;
        y --;
    }
}

int get_height(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    return height;
}
