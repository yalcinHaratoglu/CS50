#include <cs50.h>
#include <stdio.h>

int get_correct_int(void);

int main(void)
{
    int n = get_correct_int();
    for (int i = 0; i < n; i++)
    {
        for (int j = n; j > 0; j--)
        {
            if ((j - 2) < i)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int get_correct_int(void)
{
    int n;
    do
    {
        n = get_int("Number: ");
    }
    while (n < 1 || n > 8);
    return n;
}
