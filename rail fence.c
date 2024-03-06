#include <stdio.h>
#include <string.h>

void encryptRailFence(char *plainText, int key) 

{
    int len = strlen(plainText);
    char railMatrix[key][len];
    int i,j;
    
    for( i = 0; i < key; i++) 
	{
        for ( j = 0; j < len; j++) 
		{
            railMatrix[i][j] = ' ';
        }
    }
    int row = 0;
    int direction = 1; 

    for( i = 0; i < len; i++) 
	{
        railMatrix[row][i] = plainText[i];

        if (row == key - 1) 
		{
            direction = -1;
        } 
		else if (row == 0) 
		{
            direction = 1;
        }

        row += direction;
    }

    printf("Encrypted Text: ");
    for ( i = 0; i < key; i++) 
	{
        for ( j = 0; j < len; j++) 
		{
            if (railMatrix[i][j] != ' ') 
			{
                printf("%c", railMatrix[i][j]);
            }
        }
    }
    printf("\n");
}

int main() 
{
    char plainText[100];
    int key,i,j;

    printf("Enter the plaintext: ");
    fgets(plainText, sizeof(plainText), stdin);

    printf("Enter the key (number of rails): ");
    scanf("%d", &key);

    int len = strlen(plainText);
    if (plainText[len - 1] == '\n') 
	{
        plainText[len - 1] = '\0';
    }

    encryptRailFence(plainText, key);

    return 0;
}

