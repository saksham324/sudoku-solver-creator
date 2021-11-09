/* validateInput.c - 
* 
* Author: Sayuri Tais Miyamoto Magnabosco
* November 8th, 2021
* CS50 Fall 2021, Final Project
*
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "validateInput.h"


/************* File-local functions ************/
/* not visible outside this file */
void normalizeWord (char *word);

/************** Global functions **************/
/* that is, visible outside this file */

/*************** isValidMode() ****************/
/* validateInput.h for description */
bool 
isValidMode(char *input)
{
    normalizeWord (input);
    if (strcmp(input, "create" ) != 0 || strcmp(input, "solve" ) != 0 ){
        return false;
    }
    return true;
}

/************** isValidDifficulty() **************/
/* validateInput.h for description */
bool
isValidDifficulty(char *input)
{
    normalizeWord (input);
    if (strcmp(input, "easy" ) != 0 || strcmp(input, "hard" ) != 0 ){
        return false;
    }
    return true;
}

/* Function called by isValidDifficulty. 
* Converts all the characters of the word into lowercase. 
* 
* Caller provides:
*   a word
* We return:
*   the normalized word
*/
void
normalizeWord (char *word)
{
    if (word != NULL) {
        for (char *w = word; *w != '\0'; w++){ // for each character in the word
            *w = tolower(*w); // transforms characters to lower case
        }
    }
}