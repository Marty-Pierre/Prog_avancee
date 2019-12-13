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
#define SCREEN_WIDTH 1500 //

/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 900 //

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
#define TAILLE_CARRE 16


/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */


int main(int argc, char *argv[])
{
  bool start = false;
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
  fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_RESIZABLE);
  if (fenetre == NULL) //En cas d'erreur
    {
      printf("Erreur de la creation d'une fenetre: %s",SDL_GetError());
      SDL_Quit();
      return EXIT_FAILURE;
    }
  //Mettre en place un contexte de rendu de l'ecran
  SDL_Renderer* ecran;
  ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);


  //Creation de message pour le jeu
  TTF_Init();
  TTF_Font* police = TTF_OpenFont("./arial.ttf",65);
  SDL_Color color = {10,25,125,0};
  SDL_Surface* TextSurf = TTF_RenderText_Solid(police,"Appuyez sur le clic gauche de la souris pour jouer",color) ;
  SDL_Texture* Text = SDL_CreateTextureFromSurface(ecran,TextSurf);
  //Ou sera affiche le texte et a quelle dimensions
  SDL_Rect text_pos;
  text_pos.x = (SCREEN_WIDTH - 900) /2;
  text_pos.y = (SCREEN_HEIGHT + 400) /2;
  text_pos.w = 1000;
  text_pos.h = 200;
  
  

  //Charger l'image
  SDL_Texture* fond = charger_image("image/fond.bmp", ecran);

  //Creer le perso et l'initailiser
  perso_t nain;
  nain.vx = 0;
  nain.vy = 1; //1 car on veut que notre personnage soit soumi a la gravité
    
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
      tabPavage[0][i].x = (i % 16 ) * 32;
      tabPavage[0][i].y = (i / 16 ) * 32;
      tabPavage[0][i].w = 32;
      tabPavage[0][i].h = 32;
	
    }

  //tableau qui lie la map txt avec l'ecran
  SDL_Rect** tabDestPavage = malloc(sizeof(tabDestPavage) * mapLig);
  tabDestPavage[0] = (SDL_Rect*)malloc(sizeof(SDL_Rect) * mapCol * mapLig);
  for(int i = 0; i < mapLig * mapCol; i++)
    {
	  tabDestPavage[0][i].x = (i % mapCol) * TAILLE_CARRE;
	  tabDestPavage[0][i].y = (i / mapCol) *TAILLE_CARRE;
	  tabDestPavage[0][i].w = TAILLE_CARRE ;
	  tabDestPavage[0][i].h = TAILLE_CARRE ;
	
    }
  printf("%i, %i \n",mapLig, mapCol);

  
  
  //Creation tab 2d pour perso
  SDL_Rect** tabPerso = malloc(sizeof(*tabPerso) * 10);
  tabPerso[0] = (SDL_Rect*)malloc(sizeof(SDL_Rect) * 100);
  for(int i = 1; i < 10; i++)
    {
      tabPerso[i] = tabPerso[i-1] + 10;
    }

  for(int i = 0; i < 10; i++)
    {
      for(int j = 0; j < 10; j++)
	{
	  tabPerso[i][j].x = i * 32;
	  tabPerso[i][j].y = j * 32;
	  tabPerso[i][j].w = 32;
	  tabPerso[i][j].h = 32;
	}
    }
  SDL_Rect SrcR = tabPerso[0][0];
  
  nain.DestR.x = 100; //Position de depart du nain
  nain.DestR.y = 170;
  nain.DestR.w = TAILLE_CARRE;//(SrcR.w); //taille affiche
  nain.DestR.h = TAILLE_CARRE;//(SrcR.h);

  
  //Boucle principale
  while(!terminer)
    {
      SDL_RenderClear(ecran);
      if(start)
	{
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
	  SDL_RenderCopy(ecran, obj, &SrcR, &(nain.DestR));
	}
      else
	{
	  SDL_RenderCopy(ecran,fond,NULL,NULL);
	  SDL_RenderCopy(ecran,Text,NULL,&text_pos);
	}
      while(SDL_PollEvent(&evenements)){
	switch(evenements.type)
	  {
	  case SDL_QUIT:
	    terminer = true; break;
	  case SDL_KEYDOWN:
	    switch(evenements.key.keysym.sym)
	      {
	      case SDLK_ESCAPE:
		terminer = true; break;
		if(!start){
		case SDLK_UP:
		  nain.vy = -2;
		  nain.DestR.y = nain.DestR.y + nain.vy;
		  colision_haut(&nain, tabMap);
		  if(nain.vy != 1){
		    nain.vy = nain.vy + 1;
		}
		  break;
		case SDLK_LEFT:
		  nain.vx = - TAILLE_CARRE;
		  nain.DestR.x = nain.DestR.x + nain.vx;
		  colision_gauche(&nain, tabMap);
		  nain.vx = 0;break;
		case SDLK_RIGHT:
		  nain.vx = TAILLE_CARRE;
		  nain.DestR.x = nain.DestR.x + nain.vx;
		  colision_droit(&nain, tabMap);
		  nain.vx = 0;break;
		case SDLK_DOWN:
		  nain.DestR.y = nain.DestR.y + TAILLE_CARRE ; break;	
		case SDLK_z:
		  nain.vy = -2;
		  nain.DestR.y = nain.DestR.y + nain.vy;
		  colision_haut(&nain, tabMap);
		  if(nain.vy != 1){
		    nain.vy = nain.vy + 1;
		  }
		  break;
		case SDLK_q:
		  nain.vx = - TAILLE_CARRE;
		  nain.DestR.x = nain.DestR.x + nain.vx;
		  colision_gauche(&nain, tabMap);
		  nain.vx = 0;break;
		case SDLK_d:
		  nain.vx = TAILLE_CARRE;
		  nain.DestR.x = nain.DestR.x + nain.vx;
		  colision_droit(&nain, tabMap);
		  nain.vx = 0;break;
		case SDLK_s:
		  nain.DestR.y = nain.DestR.y + TAILLE_CARRE ; break;	
		}
		else // Si le joueur est a l'ecran de titre
		  {
		    case SDLK_k:
		      start = true; break;
		  }
		
	      }break;
	  }
      }
      
      //Permet de faire tomber le personnage, comme si il y a avait de la gravite
      nain.DestR.y = nain.DestR.y + nain.vy;
      colision_bas(&nain,tabMap);
      if(nain.vy != 1){
	nain.vy = nain.vy + 1;
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
  //Quitter ttf
  TTF_CloseFont(police);
  TTF_Quit();
  //Liberation de l'ecran (renderer)
  SDL_DestroyRenderer(ecran);
  //Quitter SDL
  SDL_DestroyWindow(fenetre);
  SDL_Quit();
  return 0;
}
