/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000


unsigned int array_from_stdin(int array[],
                             unsigned int max_size) {

    unsigned int length;
    printf("Insert the length of the array:\n");
    int assert = fscanf(stdin, "%u", &length);
    if (assert != 1){
                printf("The length needs to be a unsigned integer.\n");
                exit(EXIT_FAILURE);
            }

    if(length <= max_size){
        for(unsigned int i = 0; i < length; i++ ){
            printf("Insert the %u° element of the array:\n", i+1);
            assert = fscanf(stdin,"%d", &array[i]);
            if (assert != 1){
                printf("The element needs to be a integer.\n");
                exit(EXIT_FAILURE);
            }
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
    unsigned int length = array_from_stdin(array, MAX_SIZE);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
