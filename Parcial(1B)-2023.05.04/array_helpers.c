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

static const char* CITY_NAMES[CITIES] = {
    "Cordoba", "Rosario", "Posadas", "Tilcara", "Bariloche"};
static const char* SEASON_NAMES[SEASONS] = {"low", "high"};

static unsigned int profit(BakeryProductTable a, unsigned int city, unsigned int season){
    BakeryProduct local = a[city][season];
	unsigned int profit = (local.flour_cant * local.flour_price) + 
                          (local.yeast_cant * local.yeast_price) +
                          (local.butter_cant * local.butter_price);
    profit = local.sale_value - profit;
    return profit;
}

void array_dump(BakeryProductTable a)
{
    for (unsigned int city = 0u; city < CITIES; ++city)
    {
        for (unsigned int season = 0u; season < SEASONS; ++season)
        {
            fprintf(stdout, "%s in %s season: flour (%u,%u) Yeast (%u,%u) Butter (%u,%u) Sales value %u",
                    CITY_NAMES[city], SEASON_NAMES[season], a[city][season].flour_cant,
                    a[city][season].flour_price, a[city][season].yeast_cant,
                    a[city][season].yeast_price, a[city][season].butter_cant,
                    a[city][season].butter_price, a[city][season].sale_value);
            fprintf(stdout, "\n");
        }
    }
}

unsigned int worst_profit(BakeryProductTable a)
{
    unsigned int min_profit = profit(a, 0, 0);
    unsigned int local_profit;
    for(unsigned int city = 0u; city < CITIES; city++){
		for(unsigned int season = 0u; season < SEASONS; season++){
			local_profit = profit(a, city, season);
			if(local_profit < min_profit){
				min_profit = local_profit;
			}
        }
    }
    return min_profit;
}

void array_from_file(BakeryProductTable array, const char* filepath)
{
    FILE* file = NULL;

    file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (!feof(file) && i < (CITIES * SEASONS))
    {
        unsigned int city_id, city_season;
        int res = fscanf(file, "##%u\?\?%u\n", &city_id, &city_season);
	    if (res != EXPECTED_DIM_VALUE)
        {
            fprintf(stderr, "Invalid file.\n");
            exit(EXIT_FAILURE);
        }
        BakeryProduct product = bakery_product_from_file(file);
        if(city_id > 5 || city_season > 2){
		  printf("Invalid city or season.\n");
		  exit(EXIT_FAILURE);
        }
        array[city_id][city_season] = product;

        ++i;
    }
    fclose(file);
}
