/* validateInput.h - header file for CS50 'validateInput' module
* 
* Author: Sayuri Tais Miyamoto Magnabosco
* November 8th, 2021
* CS50 Fall 2021, Final Project
*
*/ 
#ifndef __VALIDATEINPUT_H
#define __VALIDATEINPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/**************** Global types ****************/
//none

/****************** Functions *****************/

/*************** isValidMode() ****************/
/* Checks if the user input for the mode is a valid
* option, that is "create" or "solve"
*
* Caller provides:
*   the input string of the "mode" 
* We return:
*   TRUE if input is either "create" or "solve", FALSE otherwise
* Notes:
*   We call normalizeWord() to make the input string into lowercase
*/
bool isValidMode(char *input);

/************ isValidDifficulty() ************/
/* Checks if the user input for the difficulty is a valid
* option, that is "easy" or "hard"
*
* Caller provides:
*   the input string of the "difficulty" 
* We return:
*   TRUE if input is either "easy" or "hard", FALSE otherwise
* Notes:
*   We call normalizeWord() to make the input string into lowercase
*/
bool isValidDifficulty(char *input);

#endif // __VALIDATEINPUT_H