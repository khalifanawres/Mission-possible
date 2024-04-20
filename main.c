#include <SDL/SDL.h>
#include "tic.h"

int main() {
  
    tic t;
    int continuer=1;
    SDL_Event event;
    SDL_Surface *ecran;
    t.tour=1;
    initialiserTic(&t);

    while (continuer) {
        afficherTic(t,ecran);

        if (t.tour <9 && atilgagner(t.tabsuivi)==0) {
            if ((t.tour % 2) == 1) {
                calcul_coup(t.tabsuivi);
                t.tour++;
            } else {
                SDL_WaitEvent(&event);
                if (event.type == SDL_MOUSEBUTTONUP) {
                } else if (event.type == SDL_QUIT) {
                    continuer = 0;
                }
            }
        } else {
            resultat(t.tabsuivi, ecran);
            continuer=0;
        }
    }

    liberer(t);
    return 0;
}
