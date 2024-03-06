#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5

void prepareKeyTable(char key[], char keyTable[SIZE][SIZE]) 
{
    int i, j, k, len;
    char *keystr = (char *)malloc(26 * sizeof(char));
    for (i = 0; i < strlen(key); i++) 
	{
        key[i] = toupper(key[i]);
    }
    len = 0;
    for (i = 0; i < strlen(key); i++) 
	{
        if (key[i] != 'J') 
		{
            keystr[len++] = key[i];
        }
    }
    for (i = 'A'; i <= 'Z'; i++) 
	{
        if (i != 'J' && !strchr(keystr, i)) 
		{
            keystr[len++] = i;
        }
    }
    k = 0;
    for (i = 0; i < SIZE; i++) 
	{
        for (j = 0; j < SIZE; j++) 
		{
            keyTable[i][j] = keystr[k++];
        }
    }
}

void searchPosition(char keyTable[SIZE][SIZE], char ch, int *row, int *col) 
{
    int i, j;

    for (i = 0; i < SIZE; i++) 
	{
        for (j = 0; j < SIZE; j++) 
		{
            if (keyTable[i][j] == ch) 
			{
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encrypt(char keyTable[SIZE][SIZE], char plaintext[], char ciphertext[]) 
{
    int i, len, row1, row2, col1, col2;
    char pair[2];

    len = strlen(plaintext);

    for (i = 0; i < len; i += 2) 
	{
        pair[0] = plaintext[i];
        pair[1] = (i + 1 < len) ? plaintext[i + 1] : 'X';

        searchPosition(keyTable, pair[0], &row1, &col1);
        searchPosition(keyTable, pair[1], &row2, &col2);

        if (row1 == row2) 
		{
            pair[0] = keyTable[row1][(col1 + 1) % SIZE];
            pair[1] = keyTable[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) 
		{
            pair[0] = keyTable[(row1 + 1) % SIZE][col1];
            pair[1] = keyTable[(row2 + 1) % SIZE][col2];
        } else {
            pair[0] = keyTable[row1][col2];
            pair[1] = keyTable[row2][col1];
        }

        ciphertext[i] = pair[0];
        ciphertext[i + 1] = pair[1];
    }
}

int main() 
{
    char key[25], plaintext[100], ciphertext[100], keyTable[SIZE][SIZE];

    printf("Enter the key: ");
    scanf("%s", key);

    printf("Enter the plaintext: ");
    scanf("%s", plaintext);

    prepareKeyTable(key, keyTable);

    encrypt(keyTable, plaintext, ciphertext);


    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

