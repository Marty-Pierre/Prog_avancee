/**
 * \file jeu.c
 * \author Marty Pierre & Larcher Alexis
 * \date octobre 2019
 */

#include "sdl-light.h"
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

SDL_Surface* init_sdl(int width, int height){
    SDL_Surface* screen = NULL;
    
    SDL_Init( SDL_INIT_VIDEO );
    
    //Set up screen
    screen = SDL_SetVideoMode( width, height, 16, SDL_SWSURFACE| SDL_DOUBLEBUF | SDL_ANYFORMAT );
    
    return screen;
}

/** 
 *\brief La fonction permet de quitter la SDL
 * en supprimant notamment la surface correspondant à l'écran de jeu
 */

void quit_sdl(){
    SDL_Quit();
}

/**
 * \brief La fonction charge une image  et renvoie la surface SDL optimisée correspondante
 * \param path est le chemin du fichier image. Le fichier doit être obligatoirement du BMP.
 * \return la surface SDL contenant l'image. Elle renvoie NULL si le chargement a échoué
 * (ex. le fichier path n'existe pas)
 */

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
