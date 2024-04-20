#include "tic.h"

void initialiserTic(tic *t) {
    t->background = IMG_Load("images/grille.png");
    t->imageJoueur = IMG_Load("images/X.png");
    t->imageOrdinateur = IMG_Load("images/O.png");

   
    for (int i = 0; i < 9; i++) {
        t->tabsuivi[i] = 0;
    }
    t->positionCase.x = 0; 
    t->positionCase.y = 0; 
    t->tour = 0;
    
    TTF_Init();
    t->police = TTF_OpenFont("police.ttf", 24); 
    
    t->couleurTexte = {255, 255, 255};
    strcpy(t->texteFinPartie, "");
    t->positionTexte.x = 0; 
    t->positionTexte.y = 0;
}

void afficherTic(tic t, SDL_Surface *ecran) {
   
    SDL_BlitSurface(t.background, NULL, ecran, NULL);

    for (int i = 0; i < 9; i++) {
        int ligne = i / 3;
        int colonne = i % 3;
        SDL_Rect position = {t.positionCase.x + colonne * LARGEUR_CASE, t.positionCase.y + ligne * HAUTEUR_CASE};
        if (t.tabsuivi[i] == -1) {
            SDL_BlitSurface(t.imageJoueur, NULL, ecran, &position);
        } else if (t.tabsuivi[i] == 1) {
            SDL_BlitSurface(t.imageOrdinateur, NULL, ecran, &position);
        }
    }

    
    if (strcmp(t.texteFinPartie, "") != 0) {
        SDL_Surface *texteSurface = TTF_RenderText_Solid(t.police, t.texteFinPartie, t.couleurTexte);
        SDL_BlitSurface(texteSurface, NULL, ecran, &t.positionTexte);
        SDL_FreeSurface(texteSurface);
    }

    SDL_Flip(ecran);
}
int atilganer(int tabsuivi[]) {
    int lignes_gagnantes[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}
    };

    for (int i = 0; i < 8; i++) {
        if (tabsuivi[lignes_gagnantes[i][0]] != 0 &&
            tabsuivi[lignes_gagnantes[i][0]] == tabsuivi[lignes_gagnantes[i][1]] &&
            tabsuivi[lignes_gagnantes[i][1]] == tabsuivi[lignes_gagnantes[i][2]]) {
            return tabsuivi[lignes_gagnantes[i][0]];
        }
    }
    return 0;
}
void resultat(int tabsuivi[], SDL_Surface *ecran) {
  int gagnant = atilganer(tabsuivi);
    if (gagnant == 1) {
        printf(texte, "La machine a gagne !");
    } else if (gagnant == -1) {
        printf(texte, "Le joueur a gagne !");
    } else {
        printf(texte, "Match nul !");
    }
    SDL_Surface* message = TTF_RenderText_Solid(font, text, textColor);
    SDL_BlitSurface(message, NULL, screen, &textPosition);
    SDL_Flip(screen);
    SDL_FreeSurface(message); 
}

void liberer(tic t) {
 
    SDL_FreeSurface(t.background);
    SDL_FreeSurface(t.imageJoueur);
    SDL_FreeSurface(t.imageOrdinateur);
    TTF_CloseFont(t.police);
    TTF_Quit();
}

int minmax(int tabsuivi[9], int joueur) {
    int gagnant = atilganer(tabsuivi);
    if (gagnant != 0)
        return gagnant * joueur;

    int coup = -1;
    int score = -2;
    for (int i = 0; i < 9; i++) {
        if (tabsuivi[i] == 0) {
            tabsuivi[i] = joueur;
            int mmscore = -minimax(ecran, tabsuivi, joueur * -1);
            if (mmscore > score) {
                score = mmscore;
                coup = i;
            }
            tabsuivi[i] = 0;
        }
    }
    if (coup == -1)
        return 0;
    return score;
}

void calcul_coup(int tabsuivi[9]) {
    int coup = -1;
    int score = -2;
    for (int i = 0; i < 9; i++) {
        if (tabsuivi[i] == 0) {
            tabsuivi[i] = 1;
            int mmscore = -minimax(ecran, tabsuivi, -1);
            tabsuivi[i] = 0;
            if (mmscore > score) {
                score = mmscore;
                coup = i;
            }
        }
    }
    tabsuivi[coup] = 1;
}

void liberer(tic t) {
    SDL_FreeSurface(t.background);
    SDL_FreeSurface(t.imageJoueur);
    SDL_FreeSurface(t.imageOrdinateur);
    TTF_CloseFont(t.police);
    TTF_Quit();

