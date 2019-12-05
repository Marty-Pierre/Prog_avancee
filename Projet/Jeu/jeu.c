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

/*SDL_Window* init_sdl(int width, int height){
    SDL_Window* screen = NULL;
    
    SDL_Init( SDL_INIT_VIDEO );
    
    //Set up screen
    //screen = SDL_SetVideoMode( width, height, 16, SDL_SWSURFACE| SDL_DOUBLEBUF | SDL_ANYFORMAT );
    screen = SDL_CreateWindow("Ma fenêtre de jeu", 
			      SDL_WINDOWPOS_UNDEFINED, 
			      SDL_WINDOWPOS_UNDEFINED, 
			      width, height, 
			      SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
    return screen;
}

/** 
 *\brief La fonction permet de quitter la SDL
 * en supprimant notamment la surface correspondant à l'écran de jeu
 

void quit_sdl(){
    SDL_Quit();
}

/**
 * \brief La fonction charge une image  et renvoie la surface SDL optimisée correspondante
 * \param path est le chemin du fichier image. Le fichier doit être obligatoirement du BMP.
 * \return la surface SDL contenant l'image. Elle renvoie NULL si le chargement a échoué
 * (ex. le fichier path n'existe pas)
 

SDL_Surface* load_image(char path[]){
    SDL_Surface* loadedImage = NULL;
    
    SDL_Surface* optimizedImage = NULL;
    loadedImage = SDL_LoadBMP( path);
    
    if( loadedImage != NULL ) {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage );
    }
    else{
        fprintf(stderr,"Image %s cannot be loaded!\n",path);
    }
    return optimizedImage;
    
}
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
  for(i = 0; i<c*l;i++)
    {
      tab[0][i] = 'a';
    }
  return tab;
}

void desallouer_tab_2D(char** tab)
{
  free(tab[0]);
  free(tab);
}

void afficher_tab_2D(char** tab, int l, int c)
{
  int i,j;
  for(i=0;i<c*l;i++)
    {
      printf("%c",tab[0][i]);
    }
}

void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol)
{
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

char** allouer_tab_2D(int l, int c)
{
  int i;
  char** tab = malloc(sizeof(*tab) * l);
  tab[0] = (char*) malloc(sizeof(char) * c * l);
  for(i = 1; i < l ; i++)
    {
      tab[i] = tab[i-1] + c;
    }
  /* for(i = 0; i<c*l;i++)
    {
      tab[0][i] = '';
      }*/
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
