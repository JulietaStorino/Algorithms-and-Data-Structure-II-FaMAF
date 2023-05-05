/*
  @file bakery_product.c
  @brief Implements bakery product structure and methods
*/
#include <stdlib.h>
#include "bakery_product.h"

static const int AMOUNT_OF_PRODUCT_VARS = 7;

BakeryProduct bakery_product_from_file(FILE* file)
{
    BakeryProduct product;

    if(feof(file)){
    printf("Invalid array.¸\n");
    exit(EXIT_FAILURE);
    }
    int errorvalue = fscanf(file, "%u (%u,%u) (%u,%u) (%u,%u)\n", &product.sale_value, &product.yeast_cant, &product.yeast_price, &product.butter_cant, &product.butter_price, &product.flour_cant, &product.flour_price);
    if(errorvalue != AMOUNT_OF_PRODUCT_VARS){
	    printf("Error, invalid file.\n");
            exit(EXIT_FAILURE);
    }
    
    return product;
}
