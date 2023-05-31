#include <stdlib.h>
#include "strfuncs.h"

size_t string_length(const char* str){
    
    size_t index = 0u;
    
    while(str[index] != '\0'){
        index++;
    }
    
    return index;
}

char *string_filter(const char *str, char c){
    
    size_t length = string_length(str);
    size_t index = 0u;
    
    char *result = (char *)malloc(sizeof(char)*(length + 1));
    
    for(unsigned int i = 0u; i<length; i++){
        if(str[i] != c){
            result[index] = str[i];
            index++;
        }
    }

    return result;
}