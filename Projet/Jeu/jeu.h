#ifndef __jeu_h__
#define __jeu_h__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
//#include "SDL2_image"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NB_ELEM_LARGEUR_TERRAIN 16
#define NB_ELEM_HAUTEUR_TERRAIN 10
#define NB_ELEM_LARGEUR_PERSO 95
#define NB_ELEM_HAUTEUR_PERSO 125
#define TAILLE_CARRE 16

struct terrain_s{
  SDL_Surface* terrain;
};
typedef struct terrain_s terrain_t;

struct perso_s{
  SDL_Rect DestR;
  int vx;
  int vy;
  //SDL_Surface perso;
};
typedef struct perso_s perso_t;

struct world_s{
  SDL_Surface* background;
  int gameover;
  terrain_t tab_terrain[NB_ELEM_LARGEUR_TERRAIN][NB_ELEM_HAUTEUR_TERRAIN];
  perso_t tab_perso[NB_ELEM_LARGEUR_PERSO][NB_ELEM_HAUTEUR_PERSO];
};
typedef struct world_s world_t;

SDL_Texture* charger_image(const char* nomfichier, SDL_Renderer* renderer);
SDL_Texture* charger_image_transparente(const char* nomfichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
char** allouer_tab_2D(int l, int c);
void desallouer_tab_2D(char** tab);
void afficher_tab_2D(char** tab, int l, int c);
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);
char** lire_fichier(const char* nomFichier);
void colision_haut(perso_t* pers, char** map);
void colision_bas(perso_t* pers, char** map);
void colision_gauche(perso_t* pers, char** map);
void colision_droit(perso_t* pers, char** map);
/*
SDL_Window* init_sdl(int width, int height);
void quit_sdl();hhhh
SDL_Surface* load_image(char path[]);


void init_data(world_t * world);
*/

#endif
