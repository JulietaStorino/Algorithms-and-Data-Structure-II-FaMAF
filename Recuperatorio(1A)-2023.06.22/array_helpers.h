/*
  @file array_helpers.h
  @brief defines array helpers methods. These methods operates over multidimensional array of layover
*/
#ifndef _ARRAY_HELPERS_H
#define _ARRAY_HELPERS_H

#include <stdbool.h>
#include "wagon.h"

#define MAX_SIZE 100
#define SECTIONS 2


typedef Wagon Train [MAX_SIZE][SECTIONS];

/**
 * @brief Write the content of the array 'a' into stdout.
 * @param[in] a array to dump in stdout
 */
void array_dump(Train t, unsigned int size);

/**
 * @brief indicates if any group of wagons should be discarded.
 * @param[in] a array
 */
bool has_to_discard_wagons(Train t, unsigned int trainSize);


/**
 * @brief reads an array of train information from file
 * @details
 *
 *  Each element is read from the file located at 'filepath'.
 *  The file must exist in disk and must have its contents in a sequence of
 *  lines, first line will be:
 *
 *   [<train code>]  #<number of wagons> <total_weight>kg
 *
 *   and then each following line will have the following format:
 *
 *   <wagon number> <cargo type> <kg> <cargo type> <kg>
 *
 *   Those elements are copied into the array 'a'.
 *   The dimensions of the array are given by the macros noted above.
 *
 * @param a array which will contain read file
 * @param trainSize output parameter where the actual number of read wagons are
 *        store
 * @param filepath file with train data
 */
void array_from_file(Train t, unsigned int * trainSize, const char *filepath);

#endif
