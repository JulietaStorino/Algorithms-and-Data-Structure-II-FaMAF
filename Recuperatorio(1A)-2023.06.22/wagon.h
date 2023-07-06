/*
  @file wagon.h
  @brief Defines a train wagon cargo
*/

#ifndef _WAGON_H
#define _WAGON_H
#define EXPECTED_WAGON_LINE_FORMAT " %c %u "

typedef enum { rice, mushrooms, oatmeal, pepper } cargo_t;

typedef enum { primary, secondary} section_t;

#include <stdio.h>

/** @brief Type used to represent wagon cargo data.*/
typedef struct _wagon
{
  unsigned int number;
  section_t section;
  cargo_t cargo;
  unsigned int weight;
} Wagon;

/**
 * @brief reads cargo data from file line
 * @details
 * Cargo file line must contain:
 * <char*> <unsigned int>
 *
 * @param[in] wagon_num the previously read identification number of the wagon
 *                      for that is gathering information from file
 * @param[in] section indicates which section corresponds to this cargo
 * @param[in] file Opened file stream
 * @return Wagon structure with all components filled with the information read
 *               from file and with the supplied parameters
 *
 */
Wagon wagon_from_file(unsigned int wagon_num, section_t section, FILE* file);

#endif //_WAGON_H
