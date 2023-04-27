#include <stdio.h>
#include <stdlib.h>
#include "enigme.h"

int main(int argc, char const *argv[])
{
    SDL_Surface *screen;

    SDL_Event event;

    enigme e;

    SDL_Init(SDL_INIT_EVERYTHING);

    screen = SDL_SetVideoMode(1000, 800, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    TTF_Init();

    int loop = 1;

    int alea;
    int startTime;

    init_enigme(&e);

    SDL_Color textColor = {255, 255, 255};

    showText(screen, e.font, textColor, "Press T for the enigme", 0, 0);

    while (loop)
    {

        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            loop = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_t:

                startTime = SDL_GetTicks() / 1000;

                generate_afficher(screen, &e, &alea);

                int answer = resolution(screen, e, &loop, startTime); // -1

                if (answer == e.reponse)
                    afficher_resultat(screen, 1, &e);
                else
                    afficher_resultat(screen, -1, &e);
                break;
            }
        }

        SDL_Flip(screen);
    }

    SDL_FreeSurface(e.background);
    SDL_FreeSurface(e.question);
    SDL_FreeSurface(e.reponses[0]);
    SDL_FreeSurface(e.reponses[1]);
    SDL_FreeSurface(e.reponses[2]);
    TTF_CloseFont(e.font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
