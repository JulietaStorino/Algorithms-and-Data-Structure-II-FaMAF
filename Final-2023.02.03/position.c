#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "position.h"

struct _position {
        unsigned int row;
        unsigned int column;
        unsigned int dimension;
};


position_t position_initial(unsigned int dimension)
{
        position_t pos = malloc(sizeof(struct _position));
        pos->row = 0u;
        pos->column = 0u;
        pos->dimension = dimension;

        return pos;
}

position_t position_absolute(unsigned int row, unsigned int column,
                             unsigned int dimension)
{
        assert((row<dimension) && (column<dimension));
        
        position_t pos = malloc(sizeof(struct _position));
        pos->row = row;
        pos->column = column;
        pos->dimension = dimension;

        return pos;
}

position_t position_left(position_t pos)
{
        assert(pos != NULL);

        unsigned int pc = pos->column;
        unsigned int pd = pos->dimension;
        if(pc==0){
                pos->column = pd - 1;
        }else{
                pos->column = pc - 1;
        }

        return pos;
}

position_t position_right(position_t pos)
{
        assert(pos != NULL);

        unsigned int pc = pos->column;
        unsigned int pd = pos->dimension;
        if(pc == (pd-1)){
                pos->column = 0;
        }else{
                pos->column = pc + 1;
        }

        return pos;
}

position_t position_down(position_t pos)
{
        assert(pos != NULL);

        unsigned int pr = pos->row;
        unsigned int pd = pos->dimension;
        if(pr!=(pd-1)){
                pos->row = pr + 1;
        } else {
                pos->row = 0;
        }
        return pos;
}

position_t position_up(position_t pos)
{
        assert(pos != NULL);

        unsigned int pr = pos->row;
        if(pr!=0){
                pos->row = pr - 1;
        } else {
                pos->row = pos->dimension - 1;
        }

        return pos;
}

unsigned int position_row(position_t pos)
{
        assert(pos != NULL);

        return pos->row;
}

unsigned int position_column(position_t pos)
{
        assert(pos != NULL);

        return pos->column;
}

unsigned int **position_board(position_t pos)
{
        assert(pos != NULL);

        unsigned int pd = pos->dimension;
        unsigned int **board;
        board = malloc(pd * sizeof(unsigned int *));
        for(unsigned int i=0u; i<pd; i++){
                board[i] = malloc(pd * sizeof(unsigned int));           
        }
        for(unsigned int r=0u; r<pd; r++){
                for(unsigned int c=0u; c<pd; c++){
                        board[r][c] = 0;
                }
        }
        board[pos->row][pos->column] = 1u;

        return board;
}

list_t position_movements(position_t pos)
{
        assert(pos != NULL);

        list_t list = list_empty();
        for(unsigned int i = 0u; i < pos->column; i++){
                list = list_append(list, RIGHT);
        }
        for(unsigned int i = 0u; i < pos->row; i++){
                list = list_append(list, DOWN);
        }
        
        return list;
}

unsigned int position_movements_length(position_t pos)
{
        assert(pos != NULL);

        unsigned int res = pos->row + pos->column;

        return res;
}

position_t position_destroy(position_t pos)
{
        assert(pos != NULL);

        free(pos);

        pos = NULL;

        return pos;
}
