#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct 
{
    char letter;
    char cipher;
} key;

char* substitution(key key[26], char text[1000]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    key key[26];
    for (int i = 0; i < 26; i++)
    {
        key[i].letter = 'A' + i;
        key[i].cipher = argv[1][i];
    }

    char plaintext[1000];
    printf("plaintext: ");
    scanf("%[^\n]", plaintext);

    char* ciphertext = substitution(key, plaintext);

    printf("ciphertext: %s\n", ciphertext);

    free(ciphertext);

    return 0;
}

char* substitution(key key[26], char text[1000])
{
    char* cipher = (char*)malloc(strlen(text) + 1);

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            for (int j = 0; j < 26; j++)
            {
                if (toupper(text[i]) == key[j].letter)
                {
                    if (islower(text[i]))
                    {
                        cipher[i] = tolower(key[j].cipher);
                    }
                    else
                    {
                        cipher[i] = toupper(key[j].cipher);
                    }
                }
            }
        }
        else
        {
            cipher[i] = text[i];
        }
    }

    cipher[strlen(text)] = '\0'; 

    return cipher;
}