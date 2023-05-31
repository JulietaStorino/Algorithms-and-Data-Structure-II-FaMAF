#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    if (x >= 0){
        y = x;
    }else{
        y = -x;
    }
}

int main(void) {
    int a=0, res=0;
    a = -10;
    absolute(a, res);
    printf("%d\n", res);
    return EXIT_SUCCESS;
}

/*El valor que se muestra al hacer printf es el
valor con el cual inicializamos la variable res, ya
que la función absolute solo modifica la copia que
hace al valor de la variable y, que le damos, y no nos 
devuelve el valor de la misma.*/