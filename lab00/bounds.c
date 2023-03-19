#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
    struct bound_data res;
    res.is_upperbound = true;
    res.is_lowerbound = true;
    res.exists = false;

    for(unsigned int i = 0; i < length; i++){
	if(arr[i] < value){
		res.is_lowerbound = false;
	}else if(arr[i] > value){
		res.is_upperbound = false;
	}else{
		res.exists = true;
		res.where = i;
	}
    }
    return res;
}

int main(void) {
    int a[ARRAY_SIZE] = {0, -1, 9, 4};
    int value=9;
    
    printf("Insert the first element of the array\n");
    scanf("%d", &a[0]);
    printf("Insert the second element of the array\n");
    scanf("%d", &a[1]);
    printf("Insert the third element of the array\n");
    scanf("%d", &a[2]);
    printf("Insert the fourth element of the array\n");
    scanf("%d", &a[3]);
    printf("Insert the value to be compared\n");
    scanf("%d", &value);
    
    struct bound_data result = check_bound(value, a, ARRAY_SIZE);
    
    if((result.is_upperbound == true) && (result.exists == false)){
	    printf("The inserted value is a upper bound of the array.\n");
    }
    if((result.is_upperbound == true) && (result.exists == true)){
            printf("The inserted value is a maximum of the array and it is in the position %u.\n", result.where);
    }
    if((result.is_lowerbound == true) && (result.exists == false)){
            printf("The inserted value is a lower bound of the array.\n");
    }
    if((result.is_lowerbound == true) && (result.exists == true)){
            printf("The inserted value is a maximum of the array and it is in the position %u.\n", result.where);
    }
    if((result.is_upperbound == false) && (result.is_lowerbound == false)){
	    printf("The inserted value is not a lower or upper bound.\n");
    }

    return EXIT_SUCCESS;
}

