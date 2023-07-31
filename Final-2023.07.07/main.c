#include <stdio.h>
#include <stdlib.h>

#include "playerOnB.h"

static void board_fron_array(type_t* a, unsigned int size)
{
    if(size == 0){
        printf("[]");
    }else{
        printf("[ ");
        for(unsigned int i = 0u; i < size; i++){
            if(a[i] == Road){
                printf("R ");
            } else if(a[i] == City){
                printf("C ");
            } else{
                printf("T ");
            }
        }
    printf("]\n");
    }
}

static void test_case1()
{
    //Creates a board
    printf("Empty case\n");
    PlayerOnB player = playerOnB_empty();
    printf("Original Board: ");
    playerOnB_print(player);

    //Try to modify the board
    player = playerOnB_upgrade_town(player, 0);
    printf("Modificated Board: ");
    playerOnB_print(player);


    //Print if its a valid board, the score and size
    printf("The player on Board is valid?: %s\n", playerOnB_is_valid(player)? "True": "False");
    printf("Player on Board score: %u\n", playerOnB_get_score(player));
    printf("Player on Board size: %u\n", playerOnB_size(player));

    //Copy the data into a array
    printf("Board from array: ");
    type_t *array = playerOnB_array(player);
    board_fron_array(array, playerOnB_size(player));
    
    //Destroy the array and free memory
    player = playerOnB_destroy(player);
    free(array);
    printf("\n\n");
}

static void test_case2()
{
    //Creates a board
    printf("Wrong case\n");
    PlayerOnB player = playerOnB_empty();
    playerOnB_add_Road(player);
    playerOnB_add_Town(player);
    playerOnB_add_Town(player);
    printf("Original Board: ");
    playerOnB_print(player);

    //Try to modify the board
    player = playerOnB_upgrade_town(player, 0);
    player = playerOnB_upgrade_town(player, 1);
    player = playerOnB_upgrade_town(player, 2);
    printf("Modificated Board: ");
    playerOnB_print(player);

    //Print if its a valid board, the score and size 
    printf("The player on Board is valid?: %s\n", playerOnB_is_valid(player)? "True": "False");
    printf("Player on Board score: %u\n", playerOnB_get_score(player));
    printf("Player on Board size: %u\n", playerOnB_size(player));

    //Copy the data into a array
    printf("Board from array: ");
    type_t *array = playerOnB_array(player);
    board_fron_array(array, playerOnB_size(player));
    
    //Destroy the array and free memory
    player = playerOnB_destroy(player);
    free(array);
    printf("\n\n");
}

static void test_case3()
{
    //Creates a board
    printf("Valid case\n");
    PlayerOnB player = playerOnB_empty();
    playerOnB_add_Town(player);
    playerOnB_add_Road(player);
    playerOnB_add_Road(player);
    playerOnB_add_Town(player);
    printf("Original Board: ");
    playerOnB_print(player);

    //Try to modify the board
    player = playerOnB_upgrade_town(player, 0);
    player = playerOnB_upgrade_town(player, 1);
    player = playerOnB_upgrade_town(player, 2);
    printf("Modificated Board: ");
    playerOnB_print(player);

    //Print if its a valid board, the score and size
    printf("The player on Board is valid?: %s\n", playerOnB_is_valid(player)? "True": "False");
    printf("Player on Board score: %u\n", playerOnB_get_score(player));
    printf("Player on Board size: %u\n", playerOnB_size(player));

    //Copy the data into a array
    printf("Board from array: ");
    type_t *array = playerOnB_array(player);
    board_fron_array(array, playerOnB_size(player));

    //Destroy the board and free memory
    player = playerOnB_destroy(player);
    free(array);
}

int main(void)
{
    test_case1();
    test_case2();
    test_case3();
    return EXIT_SUCCESS;
}
