#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"
#define MAX_STRING_LENGTH 1000

int main(void) {

    char a[MAX_STRING_LENGTH];
    printf("Insert the first word to be compared:\n");
    scanf("%s", a);
    string first = string_create(a);
    
    char b[MAX_STRING_LENGTH];
    printf("Insert the second word to be compared:\n");
    scanf("%s", b);
    string second = string_create(b);

    
    printf("The words are equal: %s.\n", string_eq(first, second)?"True":"False");
    printf("The first word is less than the second: %s.\n", string_less(first, second)?"True":"False");
    printf("The second word is less than the first: %s.\n", string_less(second, first)?"True":"False");
}