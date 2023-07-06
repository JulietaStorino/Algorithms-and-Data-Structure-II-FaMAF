/*
  @file main.c
  @brief Defines main program function
*/

/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h"

/**
 * @brief print usage help
 * @param[in] program_name Executable name
 */
void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Load train wagon data from a given file in disk.\n"
           "\n"
           "The input file must exist in disk and the first line must have the"
           "following format:\n\n"
           "[<train-code>] #<total-number-of-wagons> <total-weight>kg \n\n"
           "then, the following lines must have format:\n\n"
           "<wagon number> <cargo type> <kg> <cargo type> <kg> \n\n"
           "Those elements will be copied into the integer array 't'.\n"
           "\n\n",
           program_name);
}

/**
 * @brief reads file path from command line
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return An string containing read filepath
 */
char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

/**
 * @brief Main program function
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* create an array with the type of flight */
    Train array;
    unsigned int trainSize;

    /* parse the file to fill the array and obtain the actual length */
    array_from_file(array, &trainSize, filepath);

    /* show the data on the screen */
    array_dump(array, trainSize);

    /* Separate wagon's data output from discard information */
    printf("\n\n");

    /* Show message indicating if has to discard wagons */
    bool discard = has_to_discard_wagons(array, trainSize);
    printf("\n%s to discard wagons.\n", discard?"Has":"Has not");

    return (EXIT_SUCCESS);
}