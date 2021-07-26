#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
/******************************************************************
Program Name: substitution
Author: Darin Kishore
Date: Started 7/18/21

Definitely refactoring this one.

Description: Given a CLI substitution key AND plaintext to encrypt,
output an encrypted ciphertext.
*******************************************************************/

bool valid_cli(int num_args);
bool valid_key(string low_key, int len);
string str_to_upper (string str);
string str_to_lower (string str);
string encrypt(string msg, int len, string low_key, string high_key);


int main(int argc, string argv[])
{

    if (!valid_cli(argc))  //if invalid cli input, return 1 as error indicator.
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //intialize keylength, allocate memory for two copies of both case key dicts.
    int keylen = strlen(argv[1]);
    string low_key = malloc(27);
    string high_key = malloc(27);

    if (keylen == 26)
    {
        strcpy(low_key, argv[1]);
        strcpy(high_key, argv[1]);
    }
    else
    {
        printf("INVALID KEY.\n");
        return 1;
    }

    low_key = str_to_lower(low_key);  //make both low/highkey proper cases.
    high_key = str_to_upper(high_key);

    if (!valid_key(low_key, keylen)) //see if valid key!
    {
        printf("INVALID KEY.\n");
        return 1;
    }

    string plain_msg = get_string("plaintext: ");
    int msglen = strlen(plain_msg);

    string encrypted_msg = encrypt(plain_msg, msglen, low_key, high_key);
    printf("ciphertext: %s", encrypted_msg);

    printf("\n");//unsure why, but seems like have to do this after printing ciphertext. rules?

    free(low_key);
    free(high_key);

    return 0;
}

bool valid_cli(int num_args) //checks to see if CLI arguments are acceptable.
{
    if (num_args != 2)
    {
        return false;
    }
    return true;
}

bool valid_key(string low_key, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (!isalpha(low_key[i]))
        {
            return false;
        }

        if (strchr(low_key, low_key[i]) != strrchr(low_key, low_key[i])) // if first pointer (to loc) of char diff from last pointer (to loc) of char
        {
            return false;
        }
    }
    return true;
}

string str_to_upper (string str)
{
    string upper_string = str;
    for (int i = 0, n = strlen(upper_string); i < n; i++)
    {
        upper_string[i] = toupper(upper_string[i]);
    }
    return upper_string;
}

string str_to_lower (string str)
{
    string lower_string = str;
    for (int i = 0, n = strlen(lower_string); i < n; i++)
    {
        lower_string[i] = tolower(lower_string[i]);
    }
    return lower_string;
}

string encrypt(string msg, int len, string low_key, string high_key)
{
    for (int i = 0; i < len; i++)
    {
        if (islower(msg[i]))
        {
            msg[i] = low_key[msg[i] % 'a'];
        }
        else if (isupper(msg[i]))
        {
            msg[i] = high_key[msg[i] % 'A'];
        }
    }
    return msg;
}