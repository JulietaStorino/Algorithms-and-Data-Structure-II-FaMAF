/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"
static const int EXPECTED_DIM_VALUE = 2;

static const char* CITY_NAMES [CITIES] = {
  "Cordoba", "Rosario", "Posadas", "Tilcara", "Bariloche"
};
static const char* SEASON_NAMES [SEASONS] = {"Low", "High" };


/**
* @brief returns true when reach last line in products file
* @return True when is the last line of the file, False otherwise
*/
/*static bool is_last_line(unsigned int city) {
  return city == CITIES - 1u;
}*/

void array_dump(BakeryProductTable a) {
  for (unsigned int city = 0u; city < CITIES; ++city) {
    for(unsigned int season = 0u; season < SEASONS; ++season){
      fprintf(stdout, "%s in season %s: Flour (%u,%u) Butter (%u,%u) Yeast (%u,%u) Sales value %u",
        CITY_NAMES[city], SEASON_NAMES[season], a[city][season].flour_cant, 
        a[city][season].flour_price, a[city][season].butter_cant,
        a[city][season].butter_price,  a[city][season].yeast_cant,
        a[city][season].yeast_price, a[city][season].sale_value
      );
      fprintf(stdout, "\n");   
    }
  }
}


unsigned int worst_profit(BakeryProductTable a) {
	BakeryProduct product = a[0][0];
	unsigned int result = (product.flour_cant * product.flour_price)+(product.yeast_cant * product.yeast_price)+(product.butter_cant * product.butter_price);
	for(unsigned int city = 0u; city < CITIES; city++){
		for(unsigned int season = 0u; season < SEASONS; season++){
			product = a[city][season];
			unsigned int aux = (product.flour_cant * product.flour_price)+(product.yeast_cant * product.yeast_price)+(product.butter_cant * product.butter_price);
      aux = product.sale_value - aux;
			if(aux < result){
				result = aux;
			}
  }}
	return result;
}

void array_from_file(BakeryProductTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  while(!feof(file)){
    unsigned int city_id, city_season;
	  int errorvalue = fscanf(file, "##%u\?\?%u\n", &city_id, &city_season);
	  if(errorvalue != EXPECTED_DIM_VALUE){
		  printf("Error, invalid file.\n");
		  exit(EXIT_FAILURE);
	  }
	  BakeryProduct product = bakery_product_from_file(file);
	  if(city_id > 5 || city_season > 2){
		  printf("Invalid city or season.\n");
		  exit(EXIT_FAILURE);
	  }
	  array[city_id][city_season] = product;
  }

  fclose(file);
}
