#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main(void)
{
    long n;
    do
    {
        n = get_long ("Cash: ");
    }
    while (n < 0);

    int dig = 0;
    int twoDig = 0;
    int oneDig = 0;
    long auxN = n;

    while (auxN > 0)
    {
        if (auxN < 10)
        {
            oneDig = auxN;
        }
        else if (auxN > 10 && auxN < 100)
        {
            twoDig = auxN;
        }
        auxN = auxN / 10;
        dig++;
    }

    if (dig == 15 || dig == 13 || dig == 16) {
        int resultFinal = 0;
        long first = n;
        while (first > 0)
        {
            first = first / 10;

            int result = (first % 10) * 2;

            if (result >= 10)
            {
                int resultAux = result;
                while (resultAux > 0)
                {
                    int aux = resultAux % 10;
                    resultFinal += aux;
                    resultAux = resultAux / 10;
                }
            }
            else
            {
                resultFinal += result;
            }
            first = first / 10;
        }

        long second = n;
        while (second > 0)
        {
            int resultSecond = second % 10;
            resultFinal += resultSecond;
            second = second / 100;
        }

        if (resultFinal % 10 == 0)
        {
            // American Express -> 15 digits, start with 34 or 37
            if (dig == 15 && (twoDig == 34 || twoDig == 37))
            {
                printf("AMEX\n");
            }
            // Visa -> 13 or 16 digits, start with 4
            else if ((dig == 13 || dig == 16) && oneDig == 4)
            {
                printf("VISA\n");
            }
            // MasterCard -> 16 digits, starts with 51,52,53,54 or 55
            else if (dig == 16 && (twoDig == 51 || twoDig == 52 || twoDig == 53 || twoDig == 54 || twoDig == 55))
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }

        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }








}