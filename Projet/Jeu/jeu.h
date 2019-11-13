#ifndef __jeu_h__
#define __jeu_h__
#define NB_ELEM_LARGEUR_TERRAIN 16
#define NB_ELEM_HAUTEUR_TERRAIN 10
#define NB_ELEM_LARGEUR_PERSO 95
#define NB_ELEM_HAUTEUR_PERSO 125
#define TAILLE_CARRE 32
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct terrain_s{
  SDL_Surface* terrain;
};
typedef struct terrain_s terrain_t;

struct perso_s{
  double hauteur;
  double largeur;
  SDL_Surface perso;
};
typedef struct perso_s perso_t;

struct world_s{
  SDL_Surface* background;
  int gameover;
  terrain_t tab_terrain[NB_ELEM_LARGEUR_TERRAIN][NB_ELEM_HAUTEUR_TERRAIN];
  perso_t tab_perso[NB_ELEM_LARGEUR_PERSO][NB_ELEM_HAUTEUR_PERSO];
};
typedef struct world_s world_t;

SDL_Surface* init_sdl(int width, int height);
void quit_sdl();
SDL_Surface* load_image(char path[]);


void init_data(world_t * world);


#endif
