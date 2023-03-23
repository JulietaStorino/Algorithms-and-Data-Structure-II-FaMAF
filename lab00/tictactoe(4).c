#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */
#define DIMENSION 4

#define CELL_MAX (DIMENSION * DIMENSION - 1)

void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");

}

void print_board(char board[DIMENSION][DIMENSION])
{
    int cell = 0;

    print_sep(DIMENSION);
    for (int row = 0; row < DIMENSION; ++row) {
        for (int column = 0; column < DIMENSION; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(DIMENSION);
    }
}

char get_winner(char board[DIMENSION][DIMENSION])
{
    char winner = '-';
    for(unsigned int i = 0; (i < DIMENSION) && (winner == '-'); i++){
        bool rowview = true;
        for(unsigned int j = 0; j < DIMENSION - 1; j++){
            rowview = rowview && (board[j][i] == board[j+1][i]);
        }
    	if(rowview && (board[0][i] != '-')){
		    winner = board[0][i];
    	}
        bool columnview = true;
        for(unsigned int j = 0; j < DIMENSION - 1; j++){
            columnview = columnview && (board[i][j] == board[i][j+1]);
        }
    	if(columnview && (board[i][0] != '-')){
		    winner = board[i][0];
    	}
    }
    bool diagonalview = true;
    for(unsigned int i = 0; i < DIMENSION - 1; i++){
    diagonalview = diagonalview && (board[i][i] == board[i+1][i+1]);
    }
    if(diagonalview && (board[0][0] != '-')){
	    winner = board[0][0];
    }
    bool invdiagonalview = true;
    for(unsigned int i = 0; i < DIMENSION - 1; i++){
        for(unsigned int j = DIMENSION - 1; j > 0; j--){
            invdiagonalview = invdiagonalview && (board[i][j] == board[i+1][j-1]);
        }
    }
    if(invdiagonalview && (board[0][DIMENSION-1] != '-')){
	    winner = board[0][DIMENSION-1];
    }
    return winner;
}

bool has_free_cell(char board[DIMENSION][DIMENSION])
{
    bool free_cell=false;
    for(unsigned int i = 0; i < DIMENSION && !free_cell; i++){
	    for(unsigned int j = 0; j < DIMENSION && !free_cell; j++){
		    if(board[i][j] == '-'){
			    free_cell = true;
		    }
	    }
    }
    return free_cell;
}

int main(void)
{
    printf("TicTacToe [CoMpLeTo :D]\n");

    char board[DIMENSION][DIMENSION];
    for(unsigned int i = 0; i < DIMENSION; i++){
        for(unsigned int j = 0; j < DIMENSION; j++){
            board[i][j]='-';
        }
    }

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / DIMENSION;
            int colum = cell % DIMENSION;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;
}
