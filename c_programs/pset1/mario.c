#include <stdio.h>
#include <cs50.h>

/***********************************************************
Program Name: Mario
Author: Darin Kishore
Date: Submitted 7/14/21

Description: Prints hashes in the way the CS50 people wanted
them to be printed.
Darin desigend and implemented every method.
************************************************************/

int get_height(void);
void build_pyramid(int height);

int main(void)
{
    build_pyramid(get_height());
}

// prompts user for and returns height of pyramid
int get_height(void)
{
    int height;
    do
    {
        height = get_int("Height: \n");
    }
    while (height > 8 || height < 1);
    return height;
}

void build_pyramid(int (height))
{
    for (int row = 1; row <= height; row++)
    {
        //places the spaces
        for (int i = 0; i < (height - row); i++)
        {
            printf(" ");
        }
        // places the hashes seperated by the middle column
        for (int j = 0; j < 2 * row; j++)
            {
                if (j == row)
                {
                    printf("  ");
                }
            printf("#");
            }
        printf("\n");
    }
}