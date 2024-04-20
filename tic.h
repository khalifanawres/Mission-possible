#ifndef TIC_H
#define TIC_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#define LARGEUR_CASE 100 
#define HAUTEUR_CASE 100

typedef struct {
    SDL_Surface *bg;
    SDL_Surface *x;
    SDL_Surface *o;
    int tabsuivi[9];
    SDL_Rect positionCase;
    int tour;
    TTF_Font *police;
    SDL_Color couleurTexte;
    char texteFinPartie[50];
    SDL_Rect positionTexte;
} tic;

void initialiserTic(tic *t);
void afficherTic(tic t, SDL_Surface *ecran);
int atilgagner(int tabsuivi[]);
void resultat(int tabsuivi[], SDL_Surface *ecran);
void liberer(tic t);
int minmax(int tabsuivi[], int joueur);
void calcul_coup(int tabsuivi[]);
#endif
