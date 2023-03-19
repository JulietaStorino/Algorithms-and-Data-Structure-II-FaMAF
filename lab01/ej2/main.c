/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000


unsigned int array_from_file(int array[],
                             unsigned int max_size) {

    unsigned int length;
    printf("Insert the length of the array:\n");
    fscanf(stdin, "%u", &length);

    if(length <= max_size){
        for(unsigned int i = 0; i < length; i++ ){
            printf("Insert the %u° element of the array:\n", i+1);
            fscanf(stdin,"%d", &array[i]);
        }
    } else {
        printf("The size of the array is greater than allowed.\n");
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


int main() {
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* ask for the length and the elements of the array */
    unsigned int length = array_from_file(array, MAX_SIZE);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
