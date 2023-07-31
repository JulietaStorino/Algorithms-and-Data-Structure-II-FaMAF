#ifndef PLAYER_ONB_H
#define PLAYER_ONB_H
#include <stdbool.h>

typedef enum
{
    Road,
    Town,
    City
} type_t;

typedef struct _PlayerOnB *PlayerOnB;
typedef unsigned int Position;

/** CONSTRUCTORES */

/**
 * @brief Devuelve un nuevo 'playerOnB' creado vacío
 *
 * @return playerOnB Nuevo 'playerOnB' creado
 */
PlayerOnB playerOnB_empty();

/**
 * @brief Agrega un nuevo camino (Road) por izquierda
 *
 * @param pob player on board al cual se le agregará el camino
 * @return PlayerOnB player on board con el camino nuevo agregado
 */
PlayerOnB playerOnB_add_Road(PlayerOnB pob);

/**
 * @brief Agrega un nuevo Pueblo (Town) por izquierda
 *
 * @param pob player on board al cual se le agregará el pueblo
 * @return PlayerOnB player on board con el pueblo nuevo agregado
 */
PlayerOnB playerOnB_add_Town(PlayerOnB pob);

/* MODIFICADORES */

/**
 * @brief Convierte el pueblo en la posición pos en una ciudad.
 *        NOTE: SI LA POSICIÓN NO es válida, el método no hace nada
 *        NOTE: SI en la POSICIÓN no hay un pueblo, el método no hace nada
 *        IMPORTANTE: ESTE MÉTODO NO TIENE PERMITIDO MODIFICAR EL DATO DEL NODO
 *        PARA HACER EL UPGRADE HAY QUE CREAR UN NODO NUEVO E INSERTARLO DONDE
 *        CORRESPONDA. Es decir, debe "reemplazar" el nodo con el nodo nuevo.
 *
 * @param pob player on board
 * @param pos posición donde se encuentra el pueblo a reemplazar por ciudad
 * @return PlayerOnB player on board con el pueblo reemplazado de ser necesario
 */
PlayerOnB playerOnB_upgrade_town(PlayerOnB pob, Position pos);

/**
 * @brief Devuelve True si el player on board es válido
 *        Es válido cuando las ciudades o pueblos están separados por al
 *        menos 2 caminos. Ejemplos:
 *        Road Road Town Road Road Road Road Town -> True
 *        Road Town -> False
 *        Road Road Town City -> False
 *
 *
 * @param pob player on board
 * @return true Si playerOnBoard es válido
 * @return false Si playerOnBoard no es válido
 */
bool playerOnB_is_valid(PlayerOnB pob);

/**
 * @brief Devuelve el puntaje del jugador en tablero
 *        El puntaje se mide contabilizando 1 punto por cada pueblo
 *        y 2 puntos por cada ciudad, los caminos no suman puntos
 *        IMPORTANTE: ESTE METODO DEBE SER CONSTANTE
 *
 * @param pob playerOnB
 * @return unsigned int Puntaje del jugador
 */
unsigned int playerOnB_get_score(PlayerOnB pob);

/**
 * @brief Devuelve la cantidad de elementos que tiene la lista de elementos
 *        del jugador en tablero (player on board)
 *        IMPORTANTE: ESTE METODO DEBE SER CONSTANTE
 *
 * @param pob player on board
 * @return unsigned int Cantidad de elementos en tablero del jugador
 */
unsigned int playerOnB_size(PlayerOnB pob);

/**
 * @brief Imprime en pantalla el jugador en tablero.
 *        IMPORTANTE: Es un método solo de lectura, no debe modificar la estructura
 *
 * @param pob playerOnB
 */
void playerOnB_print(PlayerOnB pob);

/**
 * @brief Devuelve un arreglo que representa el player on Board
 *        Este método debe pedir memoria para player on board y la memoria
 *        pedida debe ser liberada después
 * @param pob player on board
 * @return type_t* Arreglo elementos de jugador en tablero. Debe seguir
 *                 el orden de la lista.
 */
type_t *playerOnB_array(PlayerOnB pob);

/**
 * @brief Destruye el jugador en tablero en cuestión y libera todos los recursos
 *        pedidos.
 *
 * @param pob Player on board
 * @return PlayerOnB PlayerOnB luego de ser borrado
 */
PlayerOnB playerOnB_destroy(PlayerOnB pob);

#endif  // PLAYER_ON_BOARD_H
