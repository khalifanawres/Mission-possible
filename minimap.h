#ifndef FONCTIONS_H_
#define FONCTIONS_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

typedef struct
{
SDL_Surface *min;
SDL_Rect posmin;
SDL_Surface *joueur;
SDL_Rect posj;
char *url;
}
minimap;

typedef struct
{
SDL_Surface *perso;
SDL_Rect posperso;
}
personne;

typedef struct
{
SDL_Rect posback;
SDL_Surface imgback;

}
background;

typedef struct
{
SDL_Surface *anim[10];
SDL_Rect pos;
}
animation;

typedef struct
{
int x;
int y;
}
position;

void init_map(minimap *m);
void afficher_map(SDL_Surface *screen,minimap m);
void init_bonhomme(personne *bonhomme);
void afficher_bonhomme(SDL_Surface *screen,personne bonhomme);
void MAJMinimap(SDL_Rect posJoueur,  minimap *m, SDL_Rect camera, int redimensionnement);
void gestion_temps(SDL_Surface *screen, int temps);

SDL_Color GetPixel(SDL_Surface *pSurface, int x, int y);
int comparerCouleur(SDL_Color couleur1, SDL_Color couleur2);
int collisionPP(personne p,SDL_Surface *masque);
void initialisation_animation(animation *map);
void affichage_animation(animation map,SDL_Surface *screen);
void sauvegarder(personne p,background b,char *nomfichier);
void charger(personne *p,background *b,char *nomfichier);
void Liberer(minimap m);
void liberer_anim(animation map);




#endif
