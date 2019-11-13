/**
 * \file main.c
 * \brief Programme principal du jeu
 * \author Marty Pierre & Larcher Alexis
 * \date octobre 2019
 */

#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 1288

/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 725

/**
 * \brief Largeur du terrain
 */
#define NB_ELEM_LARGEUR_TERRAIN 16

/**
 * \brief Hauteur de terrain
 */
#define NB_ELEM_HAUTEUR_TERRAIN 10

/**
 * \brief Largeur du personnage
 */
#define NB_ELEM_LARGEUR_PERSO 95

/**
 * \brief Hauteur du personnage
 */
#define NB_ELEM_HAUTEUR_PERSO 125

/**
 * \brief Taille de chaque carre de terrain
 */
#define TAILLE_CARRE 32


/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */

void init_data(world_t * world){
  int i;
  world->background = load_image("image/fond.bmp");
  
}
