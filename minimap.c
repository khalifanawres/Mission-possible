#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "minimap.h"


void init_map(minimap *m)
{
m->url="minimap 0.png";
m->min=IMG_Load(m->url);
if(m->min==NULL)
{
printf("Erreur %s \n",SDL_GetError());
}
m->posmin.x=480;
m->posmin.y=25;
m->posmin.w=m->min->w;
m->posmin.h=m->min->h;
}


void afficher_map(SDL_Surface *screen,minimap m)
{
SDL_BlitSurface(m.min,NULL,screen,&m.posmin);   

}

void init_bonhomme(personne *bonhomme)
{
bonhomme->perso=IMG_Load("bonhomme.png");
if(bonhomme->perso==NULL)
{
printf("Erreur %s \n",SDL_GetError());
}
bonhomme->posperso.x=575;
bonhomme->posperso.y=220;
bonhomme->posperso.w=bonhomme->perso->w;
bonhomme->posperso.h=bonhomme->perso->h;
}


void afficher_bonhomme(SDL_Surface *screen,personne bonhomme)
{
SDL_BlitSurface(bonhomme.perso,NULL,screen,&bonhomme.posperso);   

}


void MAJMinimap(SDL_Rect posJoueur,  minimap *m, SDL_Rect camera, int redimensionnement)
{
SDL_Rect posJoueurABS;

posJoueurABS.x = posJoueur.x + camera.x;
posJoueurABS.y = posJoueur.y + camera.y;
m->posj.x=posJoueurABS.x * redimensionnement/100;
m->posj.y=posJoueurABS.y * redimensionnement/100;

}


void gestion_temps(SDL_Surface *screen, int temps)
{
char tempsaffiche[20];
SDL_Color couleurtexte;
SDL_Surface *imagetemps = NULL;
SDL_Rect postemps;
TTF_Font *police;


TTF_Init();

postemps.x = 15; 
postemps.y = 22; 

couleurtexte.r=255;
couleurtexte.g=255;
couleurtexte.b=255;

police= TTF_OpenFont("arial.ttf",18);
if (!police) 
{
       	fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
       	exit(EXIT_FAILURE);
}
snprintf(tempsaffiche, sizeof(tempsaffiche), "Temps : %d secondes", temps);

imagetemps = TTF_RenderText_Solid(police, tempsaffiche, couleurtexte);

TTF_CloseFont(police);    
SDL_BlitSurface(imagetemps, NULL,screen, &postemps);
SDL_FreeSurface(imagetemps);		

TTF_Quit();
}


SDL_Color GetPixel(SDL_Surface *pSurface, int x, int y)
{
SDL_Color color;
Uint32 col=0;
char* pPosition=(char*) (*pSurface).pixels;
pPosition+=((*pSurface).pitch*y);
pPosition+=((*(*pSurface).format).BytesPerPixel*x);
memcpy(&col,pPosition,(*(*pSurface).format).BytesPerPixel);
SDL_GetRGB(col,(*pSurface).format,&color.r,&color.g,&color.b);
return(color);

}

int comparerCouleur(SDL_Color couleur1, SDL_Color couleur2) 
{
    return couleur1.r == couleur2.r &&
           couleur1.g == couleur2.g &&
           couleur1.b == couleur2.b;
}

int collisionPP(personne p,SDL_Surface *masque)
{
int collision,x,y,w,h,i;
position pos[8];
SDL_Color Couleur_Obstacle, couleur;
couleur=GetPixel(masque,pos[i].x,pos[i].y);
Couleur_Obstacle.r=0;
Couleur_Obstacle.g=0;
Couleur_Obstacle.b=0;
x=p.posperso.x;
y=p.posperso.y;
w=p.posperso.w;
h=p.posperso.h;
pos[0].x=x;
pos[0].y=y;
pos[1].x=x+w/2;
pos[1].y=y;
pos[2].x=x+w;
pos[2].y=y;
pos[3].x=x;
pos[3].y=y+h/2;
pos[4].x=x;
pos[4].y=y+h;
pos[5].x=x+w/2;
pos[5].y=y+h;
pos[6].x=x+w;
pos[6].y=y+h;
pos[7].x=x+w;
pos[7].y=y+h/2;
collision=0;
i=0;
while((i<8)&&(collision==0))
{
if(comparerCouleur(Couleur_Obstacle,couleur))
collision=1;
i++;
}
return (collision);
}





void initialisation_animation(animation *animat)
{
//int i;
//char c[3],chemin[10]="";

animat->anim[0]=IMG_Load("minimap 0.png");
animat->anim[1]=IMG_Load("minimap 1.png");
animat->anim[2]=IMG_Load("minimap 2.png");
animat->anim[3]=IMG_Load("minimap 3.png");
animat->anim[4]=IMG_Load("minimap 4.png");
animat->anim[5]=IMG_Load("minimap 5.png");
animat->anim[6]=IMG_Load("minimap 6.png");
animat->anim[7]=IMG_Load("minimap 7.png");
animat->anim[8]=IMG_Load("minimap 8.png");
animat->anim[9]=IMG_Load("minimap 9.png");

/*for(i=1;i<=10;i++)
{
strcpy(chemin,"minimap ");
sprintf(c,"%d",i);

strcat(chemin,c);
strcat(chemin,".png");

animat->anim[i-1]=IMG_Load(chemin);
}*/

animat->pos.x=480;
animat->pos.y=25;
}

void affichage_animation( animation animat,SDL_Surface *screen)
{
int i;
for(i=0;i<10;i++)
{
SDL_BlitSurface(animat.anim[i],NULL,screen,&animat.pos);
SDL_Delay(100);
SDL_Flip(screen);
}
}



void liberer_anim(animation map)
{
int i;
for(i=0;i<=10;i++)
SDL_FreeSurface(map.anim[i]);

}

void Liberer (minimap m)
{
SDL_FreeSurface(m.min);
SDL_FreeSurface(m.joueur);
}







