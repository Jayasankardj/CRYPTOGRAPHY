#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encryptVigenere(char *plaintext, char *key) 
{
    int i, j;
    int plaintextLen = strlen(plaintext);
    int keyLen = strlen(key);

    for (i = 0, j = 0; i < plaintextLen; i++, j++) 
	{
        if (j == keyLen) 
		{
            j = 0;
        }

        char currentChar = plaintext[i];

        if (isalpha(currentChar)) 
		{
            char base = islower(currentChar) ? 'a' : 'A';
            plaintext[i] = (currentChar + key[j] - 2 * base) % 26 + base;
        } 
		else 
		{
            j--;
        }
    }
}

int main() 
{
    char plaintext[1000];
    char key[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);

    int len1 = strlen(plaintext);
    if (plaintext[len1 - 1] == '\n') 
	{
        plaintext[len1 - 1] = '\0';
    }

    int len2 = strlen(key);
    if (key[len2 - 1] == '\n') 
	{
        key[len2 - 1] = '\0';
    }

    encryptVigenere(plaintext, key);

    printf("Encrypted Text: %s\n", plaintext);

    return 0;
}

