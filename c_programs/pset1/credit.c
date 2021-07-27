#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************
Program Name: Credit
Author: Darin Kishore
Date: Submitted 7/15/21

Description: Prompt user for a credit card number,
report if (valid card), output type of card (visa, amex, etc.)

Important Functions :
turn_into_array(long num, int num_len) : changes long card
number to array of ints.
bool is_card_number(int num_len) : checks if card# valid.
void classify_card() : prints card type.

Global Vars : int* num, num_len | card #, # length.
Darin desigend and implemented every method.
************************************************************/

void turn_into_array(long num, int num_len);
string getNum(void);
void classify_card();
bool is_card_number(int num_len);
bool luhns_check();
void turn_into_array(long num, int num_len);

int* num; //main array that holds the card number .
int num_len; //length of card number .

int main(void)
{
    string temp = getNum(); //temporary string to hold card #, checks length
    num_len = strlen(temp);
    long temp_num = atol(temp);
    num = calloc((num_len-1), sizeof(int)); //dynamic memory allocation.
    turn_into_array(temp_num, num_len);

    //check if card number.
    if (!is_card_number(num_len))
    {
        printf("INVALID\n");
    }
    else
    {
        classify_card();
    }

    //prevents memleaks
    free(num);
    num = NULL;
}

//get card number !
string getNum(void)
{
    string str_num = get_string("Card Number: ");
    return str_num;
}

// turn card # into array num .
// num gives digits in order of card.
void turn_into_array(long long_num, int temp_len)
{
    //given how long the card number is, turn the card # into an array of ints.
    long temp_num = long_num;
    for (int i = num_len - 1; i >= 0; i--)
    {
        num[i] = temp_num % 10;
        temp_num /= 10;
    }
}


void classify_card()
{
    //nested cases to identify card provider after certainty of
    // card validity via length and luhns.

    // flag to trigger invalid .
    bool valid = true;

    if (num[0] == 3)     //amex check
    {
        if (num[1] == 4 || num[1] == 7)
        {
            printf("AMEX\n");
        }
        else
        {
            valid = false;
        }
    }

    else                //visa check
    if (num[0] == 4)
    {
        printf("VISA\n");
    }

    else             //mastercard check
    if (num[0] == 5)
    {
        if (num[1] == 1 || num[1] == 2 || num[1] == 3 || num[1] == 4 || num[1] == 5)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            valid = false;
        }
    }
    else
    {
        valid = false;
    }

    //case to check if luhns algo passes and valid length
    //BUT not of the "proper" starting nums
    if (valid == false)
    {
        printf("INVALID\n");
    }
}

bool is_card_number(int length)
{
    //fastest check. removes bad lengths.
    if (!(length == 13 || length == 15 || length == 16))
    {
        return false;
    }

    return luhns_check();

}

//returns true if valid via luhns, false if otherwise
bool luhns_check()
{
    //starts the luhns algorithm check. intializes temporary array to modify.
    int temp_num [num_len];
    for (int i = 0; i < num_len; i++)
    {
        temp_num[i] = num[i];
    }

    // Multiplies every other number by 2, starting with second to last
    for (int i = num_len - 2; i >= 0 ; i = i - 2)
    {
        temp_num[i] = 2 * temp_num[i];
    }

    //sums the digits
    int sum = 0, digit_sum = 0, n = 0;
    for (int i = 0; i < num_len; i++)
    {
        //ie : get digit sum
        n = temp_num[i];
        while (n > 0)
        {
            int j = n % 10;
            digit_sum += j;
            n /= 10;
        }
        sum += digit_sum;
        digit_sum = 0;
    }

    //return if valid # : D
    return((sum % 10 ) == 0);
}