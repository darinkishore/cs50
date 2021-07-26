/***********************************************************
Dictionary.c
Implements a hash-table for a dictionary.
Keys: hash(any_word_in_dict);
Values: char* word.

bulk of credit: u/fuelledbycoffee's take on u/AJ-WILLIAMS1's
implementation of gperf, which I attempted to run myself for
4 hours but didn't end up working out due to the size of the
data set.

This particular implementation removes the linked-list
component of hashing entirely, due to it being perfectly fitted
to our dict. dataset, which ensures that no duplicates are made
when hashing. This simplifies the code drastically: my own
solution for the other functions (ie: !hash()) were
almost identical to u/fuelledbycoffee's, but this is
simply a consequence of having the problem be drastically easier
due to no linked-list/tree implementation.

ie: this code is so simple because of how complex the hash
function--bless the GNU developers.
************************************************************/

#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Number of buckets in hash table
const unsigned int N = 62517665;
//word count
int word_count = 0;

// Hash table
char *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char* comp = table[hash(word)];
    if (comp != NULL)
    {
        return (strcasecmp(comp, word)==0);
    }
    return false;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    char buffer[LENGTH + 1];
    while (fscanf(dict, "%s", buffer) != EOF)
    {
        table[hash(buffer)] = strdup(buffer);
        word_count++;
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        free(table[i]);
    }
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    /* Convert it to lowercase */
    register size_t len = strlen(word);
    char            str[len + 1];
    for (int i = 0; word[i]; i++)
    {
        str[i] = tolower(word[i]);
    }

    static unsigned int asso_values[] =
    {
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 948667,   71472,    62517665,
        705,      62517665, 62517665, 62517665, 62517665, 62517665, 63481,
        56455,    58215,    62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 55,       62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        13825,    62517665, 62517665, 62517665, 62517665, 62517665, 38125,
        447264,   4505,     0,        15,       69210,    163945,   226295,
        34145,    65810,    261941,   200,      60,       20,       155,
        6487539,  719883,   40,       5,        25,       10065,    14135,
        11015,    144090,   5355,     90955,    1407881,  25750,    65,
        16578948, 26870,    2211462,  533442,   1776891,  2499207,  12282088,
        498168,   2545832,  57555,    240,      2890,     1445,     1513296,
        460,      0,        3485,     1852831,  2227297,  41245,    5,
        2648552,  275,      395,      2777837,  625863,   675,      20,
        2946112,  2384427,  1857841,  33200,    90,       2498447,  1711261,
        14855,    695508,   1505,     1302171,  402294,   308734,   461176,
        11985,    6175,     1458606,  579978,   590,      8055,     65,
        89245,    2366067,  3069567,  1775,     3125,     933963,   1909734,
        4385,     1183396,  950,      1010348,  1832291,  2210,     7310,
        95240,    1675,     2442577,  3374977,  434781,   30160,    118421,
        10165,    62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665, 62517665, 62517665, 62517665, 62517665, 62517665, 62517665,
        62517665
    };
    register unsigned int hval = len;

    switch (hval)
    {
        default:
            hval += asso_values[(unsigned char)str[19]];
        /*FALLTHROUGH*/
        case 19:
            hval += asso_values[(unsigned char)str[18]];
        /*FALLTHROUGH*/
        case 18:
            hval += asso_values[(unsigned char)str[17]];
        /*FALLTHROUGH*/
        case 17:
            hval += asso_values[(unsigned char)str[16]];
        /*FALLTHROUGH*/
        case 16:
            hval += asso_values[(unsigned char)str[15]];
        /*FALLTHROUGH*/
        case 15:
            hval += asso_values[(unsigned char)str[14] + 1];
        /*FALLTHROUGH*/
        case 14:
            hval += asso_values[(unsigned char)str[13]];
        /*FALLTHROUGH*/
        case 13:
            hval += asso_values[(unsigned char)str[12] + 1];
        /*FALLTHROUGH*/
        case 12:
            hval += asso_values[(unsigned char)str[11]];
        /*FALLTHROUGH*/
        case 11:
            hval += asso_values[(unsigned char)str[10] + 3];
        /*FALLTHROUGH*/
        case 10:
            hval += asso_values[(unsigned char)str[9] + 1];
        /*FALLTHROUGH*/
        case 9:
            hval += asso_values[(unsigned char)str[8] + 9];
        /*FALLTHROUGH*/
        case 8:
            hval += asso_values[(unsigned char)str[7]];
        /*FALLTHROUGH*/
        case 7:
            hval += asso_values[(unsigned char)str[6] + 10];
        /*FALLTHROUGH*/
        case 6:
            hval += asso_values[(unsigned char)str[5] + 11];
        /*FALLTHROUGH*/
        case 5:
            hval += asso_values[(unsigned char)str[4] + 64];
        /*FALLTHROUGH*/
        case 4:
            hval += asso_values[(unsigned char)str[3] + 52];
        /*FALLTHROUGH*/
        case 3:
            hval += asso_values[(unsigned char)str[2] + 74];
        /*FALLTHROUGH*/
        case 2:
            hval += asso_values[(unsigned char)str[1] + 35];
        /*FALLTHROUGH*/
        case 1:
            hval += asso_values[(unsigned char)str[0]];
            break;
    }

    unsigned int returnval = hval + asso_values[(unsigned char)str[len - 1]];
    return returnval % N;
}