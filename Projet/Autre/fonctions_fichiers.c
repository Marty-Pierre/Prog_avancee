#include <stdio.h>
#include <stdlib.h>
#include "fonctions_fichiers.h"

char** allouer_tab_2D(int l, int c)
{
  char** tab = malloc(sizeof(*tab) * l);
  tab[0] = (char*) malloc(sizeof(char) * c * l);
  for(int i = 1; i < l ; i++)
    {
      tab[i] = tab[i-1] + c;
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
