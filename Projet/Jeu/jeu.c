/**
 * \file jeu.c
 * \author Marty Pierre & Larcher Alexis
 * \date octobre 2019
 */

#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

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
 * \brief La fonction initialise la SDL.
 * Elle crée et renvoie la surface correspondant à l'écran du jeu
 * \param width largeur de l'écran de jeu
 * \param height hauteur de l'écran de jeu
 * \return la surface SDL correspondant à l'écran de jeu
 */



//Mettre en place un contexte de rendu de l'ecran

SDL_Texture* charger_image(const char* nomfichier, SDL_Renderer* renderer)
{
  SDL_Surface* surf = SDL_LoadBMP(nomfichier);
  return SDL_CreateTextureFromSurface(renderer, surf);
}

SDL_Texture* charger_image_transparente(const char* nomfichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b){
  //Uint32 colTrans = SDL_MapRGB(const SDL_PixelFormat* format, r, g, b);
  SDL_Surface* surf = SDL_LoadBMP(nomfichier);
  if(surf != NULL){
    // SDL_PixelFormat = SDL_PIXELFORMAT_RGB888;
    SDL_PixelFormat* pformat = surf->format;
    Uint32 colTrans = SDL_MapRGB(pformat, r, g, b);
    SDL_SetColorKey(surf, SDL_TRUE, colTrans);
    return SDL_CreateTextureFromSurface(renderer, surf);
  }else{
    printf("Pb de chargement de la texture\n");
    return NULL;
  }

}

char** allouer_tab_2D(int l, int c)
{
  int i;
  char** tab = malloc(sizeof(*tab) * l);
  tab[0] = (char*) malloc(sizeof(char) * c * l);
  for(i = 1; i < l ; i++)
    {
      tab[i] = tab[i-1] + c;
    }
  return tab;
}

void desallouer_tab_2D(char** tab){
  free(tab[0]);
  free(tab);
}

void afficher_tab_2D(char** tab, int l, int c){
  int i;
  for(i=0;i<c*l;i++)
    {
      printf("%c",tab[0][i]);
    }
}

void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol){
  FILE* fichier = NULL;
  int resLig, resCol;
  resLig = 0;
  resCol = 0;
  char ch;
  fichier = fopen(nomFichier, "r");
  while(!feof(fichier))
    {
      ch = fgetc(fichier);
      if(ch == '\n')
	{
	  resLig = resLig + 1;
	  if(*nbCol <= resCol)
	    {
	      *nbCol = resCol;
	    }
	  resCol = 0;
	}
      else
	{
	  resCol = resCol + 1;
	}
    }
  *nbLig = resLig;
  fclose(fichier);
}

char** lire_fichier(const char* nomFichier){
  FILE* fichier = fopen(nomFichier, "r");
  char ch;
  int nbLigne, nbCol;
  nbLigne = 0;
  nbCol = 0;
  taille_fichier(nomFichier,&nbLigne,&nbCol);
  char** resTabl = allouer_tab_2D(nbLigne,nbCol);
  int i = 0;
  while(!feof(fichier))
    {
      ch = fgetc(fichier);
      if(ch != '\n')
	{
	  resTabl[0][i] = ch;
	  i++;
	}
    }
  return resTabl;
}

void colision_haut(perso_t* pers, char** map){
  int xPers = pers->DestR.x / TAILLE_CARRE;
  int yPers = pers->DestR.y / TAILLE_CARRE;
  if(((map[yPers][xPers] == '0') || (map[yPers][xPers] == '2')) && ((map[yPers][xPers + 1] == '0') || (map[yPers][xPers + 1] == '2')))
    {
      pers->DestR.y =  pers->DestR.y + 1;
      printf("HAUT %i ,%i ,%c\n",xPers,yPers,map[yPers][xPers]);
      colision_bas(pers,map);
      colision_haut(pers,map);
    }
}

void colision_bas(perso_t* pers, char** map){
  int xPers = pers->DestR.x / TAILLE_CARRE;
  int yPers = pers->DestR.y / TAILLE_CARRE;
  if((map[yPers + 1][xPers] == '0') || (map[yPers + 1][xPers] == '2')) //|| (map[yPers+1][xPers+1] == '0') || (map[yPers+1][xPers+1] == '2'))
    {
      pers->DestR.y =  pers->DestR.y - 1;
      printf("BAS %i ,%i ,%c\n",xPers,yPers+1,map[yPers+1][xPers]);
      printf("BAS %i ,%i ,%c\n",xPers+1,yPers+1,map[yPers+1][xPers+1]);
      colision_haut(pers,map);
      colision_bas(pers,map);
    }
}

void colision_gauche(perso_t* pers, char** map){
  int xPers = pers->DestR.x / TAILLE_CARRE;
  int yPers = pers->DestR.y / TAILLE_CARRE;
  if(((map[yPers][xPers] == '0') || (map[yPers][xPers] == '2')) && ((map[yPers+ 1][xPers] == '0') || (map[yPers + 1][xPers] == '2')))
    {
      pers->DestR.x = pers->DestR.x + 1;
      printf("GAUCHE %i ,%i ,%c\n",xPers,yPers,map[yPers][xPers]);
      printf("GAUCHE %i ,%i ,%c\n",xPers,yPers+1,map[yPers+1][xPers]);
      colision_droit(pers,map);
      colision_gauche(pers,map);
    }
}

void colision_droit(perso_t* pers, char** map){
  int xPers = pers->DestR.x / TAILLE_CARRE;
  int yPers = pers->DestR.y / TAILLE_CARRE;
  if(((map[yPers][xPers + 1] == '0') || (map[yPers][xPers + 1] == '2')) && ((map[yPers + 1][xPers+1] == '0') || (map[yPers+1][xPers+1] == '2')))
    {
      pers->DestR.x = pers->DestR.x - 1;
      printf("DROIT %i ,%i ,%c\n",xPers+1,yPers,map[yPers][xPers+1]);
      printf("DROIT %i ,%i ,%c\n",xPers+1,yPers+1,map[yPers+1][xPers+1]);
      colision_gauche(pers,map);
      colision_droit(pers,map);
    }
}
  
