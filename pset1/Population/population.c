#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int start_size = 0;
    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);

    int end_size = 0;
    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size <= (start_size - 1));

    int cont = 0;
    while (end_size > start_size)
    {
        start_size = start_size + (start_size / 3) - (start_size / 4);
        cont++;
    }

    printf("Years: %i\n", cont);
}