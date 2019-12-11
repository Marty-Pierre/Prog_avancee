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
 *\brief gravite
 */


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

  //Creer le perso et l'initailiser
  perso_t nain;
    nain.x = 0;
    nain.y = 0;
    
  //Charger l'image du nain
  SDL_Texture* obj = charger_image("image/Dwarf.bmp", ecran);

  //Afficher une map a partir d'un fichier txt
  int mapLig = 0;
  int mapCol = 0;
  taille_fichier("map2.txt",&mapLig,&mapCol);
  char** tabMap = lire_fichier("map2.txt");
  SDL_Texture* textureMap = charger_image("image/pavage.bmp",ecran);


  //tableau de pavage
  SDL_Rect** tabPavage = malloc(sizeof(tabPavage) * 10);
  tabPavage[0] = (SDL_Rect*)malloc(sizeof(SDL_Rect) * 160);
  for(int i = 1; i < 10; i++)
    {
      tabPavage[i] = tabPavage[i-1] + 16;
    }
  
  //remplissage du tableau de pavage
  for(int i = 0; i < 160; i++)
    {
      tabPavage[0][i].x = (i % 16 ) *TAILLE_CARRE;
      tabPavage[0][i].y = (i / 16 ) *TAILLE_CARRE;
      tabPavage[0][i].w = TAILLE_CARRE;
      tabPavage[0][i].h = TAILLE_CARRE;
	
    }
  //SDL_Rect MapR = tabPavage[0][0];
  SDL_Rect** tabDestPavage = malloc(sizeof(tabDestPavage) * mapLig);
  tabDestPavage[0] = (SDL_Rect*)malloc(sizeof(SDL_Rect) * mapCol * mapLig);
  for(int i = 0; i < mapLig * mapCol; i++)
    {
	  tabDestPavage[0][i].x = (i % mapCol) * 32;
	  tabDestPavage[0][i].y = (i / mapCol) * 32;
	  tabDestPavage[0][i].w = TAILLE_CARRE ;
	  tabDestPavage[0][i].h = TAILLE_CARRE ;
	
    }

  
  
  //Creation tab 2d pour perso
  SDL_Rect** tabPerso = malloc(sizeof(*tabPerso) * 10);
  tabPerso[0] = (SDL_Rect*)malloc(sizeof(SDL_Rect) * 100);
  for(int i = 1; i < 10; i++)
    {
      tabPerso[i] = tabPerso[i-1] + 10;
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
	  tabPerso[i][j].x = i * TAILLE_CARRE;
	  tabPerso[i][j].y = j * TAILLE_CARRE;
	  tabPerso[i][j].w = TAILLE_CARRE;
	  tabPerso[i][j].h = TAILLE_CARRE;
	}
    }
  SDL_Rect SrcR = tabPerso[0][0];
  SDL_Rect DestR;
  DestR.x = nain.x;//(SCREEN_WIDTH / 2) - SrcR.w ; //position de l'objet recupere
  DestR.y = nain.y;//(SCREEN_HEIGHT / 2) - SrcR.h ;
  DestR.w = (SrcR.w) * 2; //taille affiche
  DestR.h = (SrcR.h) * 2;
  //Boucle principale
  while(!terminer)
    {
      SDL_RenderClear(ecran);
      SDL_RenderCopy(ecran, fond, NULL, NULL);
      for(int i = 0; i < mapCol * mapLig; i++)
	{
	  switch(tabMap[0][i])
	    {
	    case '0':
	      SDL_RenderCopy(ecran,textureMap,&tabPavage[5][3],&tabDestPavage[0][i]); break;
	    case '1':
	      SDL_RenderCopy(ecran,textureMap,&tabPavage[6][11],&tabDestPavage[0][i]); break;
	    case '2':
	      SDL_RenderCopy(ecran,textureMap,&tabPavage[0][8],&tabDestPavage[0][i]); break;
	    case '3':
	      SDL_RenderCopy(ecran,textureMap,&tabPavage[7][5],&tabDestPavage[0][i]); break;
	    }
	}
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
	      case SDLK_UP:
		DestR.y = DestR.y - TAILLE_CARRE ; break;
	      case SDLK_LEFT:
		DestR.x = DestR.x - TAILLE_CARRE ; break;
	      case SDLK_RIGHT:
		DestR.x = DestR.x + TAILLE_CARRE ; break;
	      case SDLK_DOWN:
		DestR.y = DestR.y + TAILLE_CARRE ; break;	
	      case SDLK_z:
		DestR.y = DestR.y - TAILLE_CARRE ; break;
	      case SDLK_q:
		DestR.x = DestR.x - TAILLE_CARRE ; break;
	      case SDLK_d:
		DestR.x = DestR.x + TAILLE_CARRE ; break;
	      case SDLK_s:
		DestR.y = DestR.y + TAILLE_CARRE ; break;	
		
	      }
	  }
      SDL_RenderPresent(ecran);
      }
  //Liberation des tableau utilises
  free(tabPerso[0]);
  free(tabPerso);
  free(tabPavage[0]);
  free(tabPavage);
  free(tabDestPavage[0]);
  free(tabDestPavage);
  desallouer_tab_2D(tabMap);
  //Liberation de l'ecran (renderer)
  SDL_DestroyRenderer(ecran);
  //Quitter SDL
  SDL_DestroyWindow(fenetre);
  SDL_Quit();
  return 0;
}
