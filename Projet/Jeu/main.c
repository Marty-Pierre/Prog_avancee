/**
 * \file main.c
 * \brief Programme principal du jeu
 * \author Marty Pierre & Larcher Alexis
 * \date octobre 2019
 */

#include "jeu.h"
//#include "SDL2_image"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 1000

/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 700

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
/*
void init_data(world_t * world){
  //int i;
  world->background = load_image("image/fond.bmp");
  
}
*/

int main(int argc, char *argv[])
{
  SDL_Window* fenetre;
  SDL_Event evenements;
  bool terminer = false;
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      printf("Erreur d'initialisition de la SDL: %s",SDL_GetError());
      SDL_Quit();
      return EXIT_FAILURE;
    }

  //Creer la fenetre
  fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
  if (fenetre == NULL) //En cas d'erreur
    {
      printf("Erreur de la creation d'une fenetre: %s",SDL_GetError());
      SDL_Quit();
      return EXIT_FAILURE;
    }
  //Mettre en place un contexte de rendu de l'ecran
  SDL_Renderer* ecran;
  ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

  //Charger l'image
  SDL_Texture* fond = charger_image("image/fond.bmp", ecran);

  //Charger l'image avec la transparence
  Uint8 r = 0, g = 255, b = 255;
  SDL_Texture* obj = charger_image("image/Dwarf.bmp", ecran);

  //Creation tab 2d pour perso
  SDL_Rect** tab = malloc(sizeof(*tab) * 10);
  tab[0] = (SDL_Rect*)malloc(sizeof(SDL_Rect) * 100);
  for(int i = 1; i < 10; i++)
    {
      tab[i] = tab[i-1] + 10;
    }
  /*
  SDL_Rect SrcR;
  SrcR.x = 0;
  SrcR.y = 0;
  SrcR.w = 32; //Largeur de l'objet a recuperer
  SrcR.h = 32; //Hauteur de l'objet a recuperer
  */
  for(int i = 0; i < 10; i++)
    {
      for(int j = 0; j < 10; j++)
	{
	  tab[i][j].x = i * TAILLE_CARRE;
	  tab[i][j].y = j * TAILLE_CARRE;
	  tab[i][j].w = TAILLE_CARRE;
	  tab[i][j].h = TAILLE_CARRE;
	}
    }
  SDL_Rect SrcR = tab[0][0];
  SDL_Rect DestR;
  DestR.x = (SCREEN_WIDTH / 2) - SrcR.w ; //position de l'objet recupere
  DestR.y = (SCREEN_HEIGHT / 2) - SrcR.h ;
  DestR.w = (SrcR.w) * 3; //taille affiche
  DestR.h = (SrcR.h) * 3;
  //Boucle principale
  while(!terminer)
    {
      SDL_RenderClear(ecran);
      SDL_RenderCopy(ecran, fond, NULL, NULL);
      SDL_RenderCopy(ecran, obj, &SrcR, &DestR);
      while(SDL_PollEvent( &evenements))
	switch(evenements.type)
	  {
	  case SDL_QUIT:
	    terminer = true; break;
	  case SDL_KEYDOWN:
	    switch(evenements.key.keysym.sym)
	      {
	      case SDLK_ESCAPE:
		terminer = true; break;
	      }
	  }
      SDL_RenderPresent(ecran);
    }
  //Liberation du tableau de sprites pour le personnage
  free(tab[0]);
  free(tab);
  
  //Liberation de l'ecran (renderer)
  SDL_DestroyRenderer(ecran);
  //Quitter SDL
  SDL_DestroyWindow(fenetre);
  SDL_Quit();
  return 0;
}
