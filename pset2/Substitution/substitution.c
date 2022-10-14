#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int isStr(string str, int lenth);
int isRepeated(string str, int lenth);

int main(int argc, string argv[])
{
    // 26 caracteres = YTNSHKVEFXRBAUQZCLWDMIPGJO
    if (argc == 1 || argc > 2)
    {
        printf("Usage: %s KEY\n", argv[0]);
        return 1;
    }
    else
    {
        int lenth = strlen(argv[1]);
        printf("lenth: %i\n", lenth);

        if (lenth < 26) // menos que 26 caracteres
        {
            printf("Key must contains 26 characters\n");
            return 1;
        }
        else if (isStr(argv[1], lenth) == 1) // Se todos os caracteres são letras
        {
            printf("Key must only contain alphabetic characters\n");
            return 1;
        }
        else if (isRepeated(argv[1], lenth) == 1) // Não pode contar caracteres repetidos
        {
            printf("Key must not contain repeated characters\n");
            return 1;
        }
        else
        {
            // Get plaintext
            // plaintext: HELLO
            string text = get_string("plaintext: ");
            printf("ciphertext: ");

            // Encipher
            // YTNSHKVEFXRBAUQZCLWDMIPGJO
            // ABCDEFGHIJKLMNOPQRSTUVWXYZ
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
                    // 72 - 65 = 7
                    // YTNSHKVE
                    // printf("%i\n", newInt);

                    char strText = argv[1][newInt]; //E

                    if (islower(text[i]))
                    {
                        printf("%c", tolower(strText));
                    }
                    else{
                        printf("%c", toupper(strText));
                    }
                }
                else
                {
                    printf("%c", text[i]);
                }
            }
            printf("\n");
            return 0;

            // Print ciphertext
            // ciphertext: JTR
        }
    }

}

int isStr(string str, int lenth)
{
    for (int i = 0; i < lenth; i++)
    {
        if(isalpha(str[i]) == false)
        {
            return 1;
        }
    }

    return 0;
}

int isRepeated(string str, int lenth)
{
    for (int i = 0; i < lenth - 1; i++)
    {
        for (int j = 1 + i; j < lenth; j++)
        {
            if (toupper(str[i]) == toupper(str[j]))
            {
                printf("%c == %c \n", str[i], str[j]);
                return 1;
            }
        }
    }

    return 0;
}
