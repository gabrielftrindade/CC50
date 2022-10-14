#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main(void)
{
    float n;
    do
    {
        n = get_float ("Cash: ");
    }
    while (n < 0 || n > 200000000);

    int centavos = round(n * 100);
    printf("Cssh %i\n", centavos);
    // 50
    // 1 5 10 25
    int total = 0;
    while (centavos > 0)
    {
        if (centavos >= 25)
        {
            centavos -= 25;
        }
        else if (centavos >= 10)
        {
            centavos -= 10;
        }
        else if (centavos >= 5)
        {
            centavos -= 5;
        }
        else
        {
            centavos -= 1;
        }

        total++;
    }

    printf("Total %i\n", total);

}