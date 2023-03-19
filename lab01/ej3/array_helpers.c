#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {
    FILE *fp = fopen(filepath, "r");

    int firtsread;
    int read = fscanf(fp, "%d\n", &firtsread);
    if (read == 0){
        printf("Invalid file.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    unsigned int length = (unsigned int) firtsread;

    if(length <= max_size){
        for(unsigned int i = 0; i < length; i++ ){
            fscanf(fp,"%d", &array[i]);
        }
        fclose(fp);
    } else {
        printf("The size of the array is greater than allowed.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    return length;
}

void array_dump(int a[], unsigned int length) {
    if(length == 0){
        printf("[]\n");
    }else{
        printf("[");
        for(unsigned int i = 0; i < length-1; i++ ){
            printf(" %d,", a[i]);
        }
        printf(" %d]\n", a[length-1]);
    }
}
