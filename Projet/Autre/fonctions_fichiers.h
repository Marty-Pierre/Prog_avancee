#ifndef FICH
#define FICH

#include <stdio.h>
#include <stdlib.h>

char** allouer_tab_2D(int l,int c);
void desallouer_tab_2D(char** tab, int n);
void afficher_tab_2D(char** tab, int l, int c);
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);
char** lire_fichier(const char* nomFichier);

#endif
