/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"
#include "wagon.h"

char * cargo_type_to_str(cargo_t cargo) {
  if (cargo == rice)
    return "rice";
  if (cargo == mushrooms)
    return "mushrooms";
  if (cargo == oatmeal)
    return "oatmeal";
  if (cargo == pepper)
    return "pepper";
  return "error";
}

static void
dump_cargo(Wagon w) {
    fprintf(stdout, "[%s cargo: %u kg of %s] ", 
                    w.section == primary ? "primary": "secondary",
                    w.weight, 
                    cargo_type_to_str(w.cargo));
}

void array_dump(Train t, unsigned int size) {
  for (unsigned int i = 0u; i < size; ++i) {
    Wagon wp = t[i][primary];
    Wagon ws = t[i][secondary];
    fprintf(stdout, "wagon %u: ", wp.number);
    dump_cargo(wp);
    dump_cargo(ws);
    if (i != size-1) {
      fprintf(stdout, "\n");
    }
  }
}

bool has_to_discard_wagons(Train t, unsigned int size) {
  bool has_to_discard = false;
  unsigned int counter = 0u;
  unsigned int index = 0u;
  while(!has_to_discard && index < size) {
    Wagon wp = t[index][primary];
    Wagon ws = t[index][secondary];

    bool case_reset = (wp.cargo != oatmeal && ws.cargo != oatmeal);
    case_reset = case_reset || ((wp.cargo == oatmeal) && (wp.weight == 0));
    case_reset = case_reset ||  ((ws.cargo == oatmeal) && (ws.weight == 0));

    counter = case_reset ? 0 : counter + 1;

    has_to_discard = (counter == 3);
    index++;
  }
  return has_to_discard;
}

// the wagon data should be saved on array
// the number of wagons should be stored on trainSize
void array_from_file(Train array, unsigned int * trainSize, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  unsigned int size = 0;
  unsigned int totalKg = 0;

  int res = fscanf(file, "[%c] #%u %ukg\n", &code, &size, &totalKg);
  if (res != 3) {
    fprintf(stderr, "Invalid file.\n");
    exit(EXIT_FAILURE);
  }

  *trainSize = size;

  unsigned int i = 0;
  while (i < size) {
    // Read wagon-number
    unsigned int wagon_number;
    int res = fscanf(file, " %u ", &wagon_number);
    if (res != 1) {
      fprintf(stderr, "Error reading wagon-number at line %u.\n", i+2);
      exit(EXIT_FAILURE);
    }

    // Read wagon's primary cargo
    Wagon wagon_primary = wagon_from_file(wagon_number, primary, file);

    // Read wagon's seconday cargo
    Wagon wagon_secondary = wagon_from_file(wagon_number, secondary, file);
  
    // Store data in array
    array[wagon_number - 1][primary] = wagon_primary;
    array[wagon_number - 1][secondary] = wagon_secondary;

    i++;
  }
  fclose(file);
}