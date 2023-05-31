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
    res.where = 0;

    for(unsigned int i = 0u; i < length; i++)
    {
	    res.is_lowerbound = res.is_lowerbound && (value <= arr[i]);
	    res.is_upperbound = res.is_upperbound && (value >= arr[i]);
	    
        if(arr[i] == value)
        {
            res.exists = true;
            res.where = i;
	    }
    }

    return res;
}

void ask_for_array(int arr[]){
    
    for(unsigned int i = 0u; i < ARRAY_SIZE; i++)
    {
        printf("Insert the %u° element of the array:\n", i+1);
        scanf("%d", &arr[i]);
    }
}

int main(void) {
    int a[ARRAY_SIZE];
    int value;

    ask_for_array(a);
    printf("Insert the value to be compared:\n");
    scanf("%d", &value);

    struct bound_data result = check_bound(value, a, ARRAY_SIZE);
    
    printf("The inserted value is a upper bound of the array: %s.\n", (result.is_upperbound ? "True": "False"));
    printf("The inserted value is a lower bound of the array: %s.\n", (result.is_lowerbound ? "True": "False"));
    printf("The inserted value is a maximum of the array: %s.\n", ((result.is_upperbound && result.exists) ? "True": "False"));
    printf("The inserted value is a minimum of the array: %s.\n", (result.is_lowerbound && result.exists) ? "True": "False");

    if(result.exists){
        printf("The inserted value is in the position %u.\n", result.where);
    }
   
    return EXIT_SUCCESS;
}
