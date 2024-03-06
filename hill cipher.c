#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 3

int determinant(int mat[MATRIX_SIZE][MATRIX_SIZE]) 
{
    return mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]) -
           mat[0][1] * (mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]) +
           mat[0][2] * (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]);
}
int x;
int modInverse(int a, int m) 
{
    a = a % m;
    for ( x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return 1;
}

void getCofactor(int mat[MATRIX_SIZE][MATRIX_SIZE], int temp[MATRIX_SIZE][MATRIX_SIZE], int p, int q, int n) 
{
    int i = 0, j = 0;
    int row,col;
    for (row = 0; row < n; row++) 
	{
        for ( col = 0; col < n; col++) 
		{
            if (row != p && col != q) 
			{
                temp[i][j++] = mat[row][col];

                if (j == n - 1) 
				{
                    j = 0;
                    i++;
                }
            }
        }
    }
}

void adjugate(int mat[MATRIX_SIZE][MATRIX_SIZE], int adj[MATRIX_SIZE][MATRIX_SIZE]) 
{
    if (MATRIX_SIZE == 1) 
	{
        adj[0][0] = 1;
        return;
    }

    int sign = 1, temp[MATRIX_SIZE][MATRIX_SIZE];
    int i,j;
    for ( i = 0; i < MATRIX_SIZE; i++) 
	{
        for ( j = 0; j < MATRIX_SIZE; j++) 
		{
            getCofactor(mat, temp, i, j, MATRIX_SIZE);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign) * (determinant(temp, MATRIX_SIZE - 1));
        }
    }
}

void encryptHill(char *block, int key[MATRIX_SIZE][MATRIX_SIZE]) 
{
    int result[MATRIX_SIZE] = {0};
    int i,j;
    for ( i = 0; i < MATRIX_SIZE; i++) 
	{
        for ( j = 0; j < MATRIX_SIZE; j++) 
		{
            result[i] += key[i][j] * (block[j] - 'A');
        }
        result[i] %= 26;
    }

    for ( i = 0; i < MATRIX_SIZE; i++) 
	{
        block[i] = result[i] + 'A';
    }
}

int main() 
{
    int key[MATRIX_SIZE][MATRIX_SIZE];
    char plaintext[1000];
    int adj[MATRIX_SIZE][MATRIX_SIZE];
    int det, detInverse;
    int i,j;
    
    printf("Enter the 3x3 key matrix:\n");
    for ( i = 0; i < MATRIX_SIZE; i++) 
	{
        for ( j = 0; j < MATRIX_SIZE; j++) 
		{
            scanf("%d", &key[i][j]);
        }
    }

    printf("Enter the plaintext (in uppercase): ");
    scanf("%s", plaintext);

    int plaintextLen = strlen(plaintext);
    if (plaintextLen % MATRIX_SIZE != 0) 
	{
        printf("Invalid plaintext length. Please enter a multiple of %d characters.\n", MATRIX_SIZE);
        return 1;
    }

    det = determinant(key);
    detInverse = modInverse(det, 26);

    adjugate(key, adj);

    for ( i = 0; i < plaintextLen; i += MATRIX_SIZE) 
	{
        encryptHill(plaintext + i, key);
    }

    printf("Encrypted Text: %s\n", plaintext);

    return 0;
}

