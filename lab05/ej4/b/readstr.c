#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20

int main(void) {
    size_t length;
    char user_input[MAX_LENGTH];

    printf("Ingrese su nombre y apellido: ");
    
    fgets(user_input, MAX_LENGTH, stdin);
    length = strlen(user_input);
    user_input[length - 1] = '\0';    

    printf("Te damos la bienvenida %s a este maravilloso programa!\n", user_input);

    return EXIT_SUCCESS;
}

