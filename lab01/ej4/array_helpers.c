#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "array_helpers.h"

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {

    FILE *fp = fopen(filepath, "r");

    unsigned int length;
    int assert = fscanf(fp, "%u\n", &length);
    if (assert != 1){
        printf("Invalid file.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    if(length <= max_size){
        for(unsigned int i = 0; i < length; i++ ){
            assert = fscanf(fp,"%d", &array[i]);
            if (assert != 1){
                printf("Invalid file.\n");
                fclose(fp);
                exit(EXIT_FAILURE);
            }
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
    if(array_is_sorted(a,length)){
        printf("The array is sorted\n");
    }else{
        printf("The array is not sorted\n");
    }
}

bool array_is_sorted(int a[], unsigned int length){
    mybool result = true;
    if(length>2){
        for(unsigned int i = 0; (i < length-1) && result; i++){
            result = result && (a[i] <= a[i+1]);
        }
    }
    return result;
}