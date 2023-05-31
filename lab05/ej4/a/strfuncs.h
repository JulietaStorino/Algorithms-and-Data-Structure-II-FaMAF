/**
*  @file strfuncs.h
*  @brief String function definitions
*/
#ifndef __STRFUNCS_H__
#define __STRFUNCS_H__

/**
* @brief Calculates the length of the string pointed to by str
* @param str A pointer to the string
* @return The length of the string
*/
size_t string_length(const char* str);

/**
* @brief returns a new string in heap memory that is obtained by taking the characters from str that are other than the character c
*/
char *string_filter(const char *str, char c);

#endif