#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int isNum(string num);
int main(int argc, string argv[])
{
    if (argc == 1 || argc > 2 || isNum(argv[1]) == 1)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    else
    {
        // printf("%i\n", argc != 2);
        // printf("%s\n", argv[1]);

        // String to Int
        int val = atoi(argv[1]);
        // printf("%i\n", val + 1);

        string text = get_string("plaintext: ");

        printf("ciphertext: ");

        for (int i = 0, n = strlen(text); i < n; i++)
        {
            if(isalpha(text[i]))
            {
                int aux = 0;
                if (islower(text[i]))
                {
                    aux = 97;
                }
                else{
                    aux = 65;
                }

                int newInt = (int) text[i] - aux;
                // printf("%i\n", newInt);
                int c = (newInt + val) % 26;
                // printf("%i\n", c);

                printf("%c", c + aux);
            }
            else
            {
                printf("%c", text[i]);
            }
        }
        printf("\n");
        return 0;
    }
}

int isNum(string num)
{
    for (int i = 0, n = strlen(num); i < n; i++)
    {
        if(isdigit(num[i]) == false)
        {
            return 1;
        }
    }

    return 0;
}