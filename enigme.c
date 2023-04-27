#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include "enigme.h"
void showText(SDL_Surface *screen, TTF_Font *font, SDL_Color color, char *text, int x, int y)
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;

    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, color);

    SDL_BlitSurface(textSurface, NULL, screen, &pos);

    SDL_FreeSurface(textSurface);
}
void init_enigme(enigme *e)
{
    int i, w;

    e->font = TTF_OpenFont("Retro.ttf", 20);
    e->PosQuestion.x = 80;
    e->PosQuestion.y = 100;

    e->PosReponse[0].x = 80;
    e->PosReponse[0].y = 300;

    e->PosReponse[1].x = 80;
    e->PosReponse[1].y = 400;

    e->PosReponse[2].x = 80;
    e->PosReponse[2].y = 500;

    e->ImageResulta = NULL;

    e->background = IMG_Load("enigme/page.png");

    e->animation.SpriteSheet = IMG_Load("enigme/animer.png");
    e->animation.pos.x = 600;
    e->animation.pos.y = 50;

    e->animation.frames = 5;
    e->animation.ClipLoaded = 0;
    for (i = 0, w = 0; i < e->animation.frames; i++, w += 265)
    {
        e->animation.Clips[i].w = 250;
        e->animation.Clips[i].h = 400;
        e->animation.Clips[i].x = w;
        e->animation.Clips[i].y = 0;
    }
}

void generate_afficher(SDL_Surface *screen, enigme *e, int *alea)
{

    SDL_Color textColor = {0, 0, 0};

    int test = *alea;

    FILE *f;
    f = fopen("enigme.txt", "r");

    do
    {
        *alea = rand() % 3;
    } while (*alea == test);

    int i = 0;
    char enigmeFull[200];

    for (i = 0; i <= *alea; i++)
        fgets(enigmeFull, 200, f);
    
    char *partieDuString = strtok(enigmeFull, ":"); 
    int j = 0;
    while (partieDuString != NULL)
    {
        if (j == 0)
            e->question = TTF_RenderText_Solid(e->font, partieDuString, textColor);
        else if (j == 4)
            e->reponse = atoi(partieDuString);
        else
            // j=2-1 =1
            e->reponses[j - 1] = TTF_RenderText_Solid(e->font, partieDuString, textColor);

        partieDuString = strtok(NULL, ":"); // B.4
        j++;
    }
    fclose(f);
}

int resolution(SDL_Surface *screen, enigme e, int *loop, int startTime)
{

    SDL_Color textColor = {255, 255, 255};

    SDL_Event event;
    int r = 0;
    int run = 1;
    while (run)
    {
        int time = (SDL_GetTicks() / 1000) - startTime;

        switch (time)
        {
        case 3:
            e.animation.ClipLoaded = 1;
            break;
        case 6:
            e.animation.ClipLoaded = 2;
            break;
        case 9:
            e.animation.ClipLoaded = 3;
            break;
        case 12:
            e.animation.ClipLoaded = 4;
            break;
        case 15:
            return -1;
            break;
        }

        SDL_FillRect(screen, NULL, 0x00000);

        SDL_BlitSurface(e.background, NULL, screen, NULL);
        SDL_BlitSurface(e.question, NULL, screen, &e.PosQuestion);

        SDL_BlitSurface(e.reponses[0], NULL, screen, &e.PosReponse[0]);
        SDL_BlitSurface(e.reponses[1], NULL, screen, &e.PosReponse[1]);
        SDL_BlitSurface(e.reponses[2], NULL, screen, &e.PosReponse[2]);

        SDL_BlitSurface(e.animation.SpriteSheet, &e.animation.Clips[e.animation.ClipLoaded], screen, &e.animation.pos);

        char timeToText[20];
        sprintf(timeToText, "%d", time);

        showText(screen, e.font, textColor, timeToText, 700, 500);
        SDL_Flip(screen);
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            *loop = 0;
            run = 0;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_a:
                r = 1;
                run = 0;
                break;
            case SDLK_b:
                r = 2;
                run = 0;
                break;
            case SDLK_c:
                r = 3;
                run = 0;
                break;
            }
            break;
        }
    }
    return r;
}

void afficher_resultat(SDL_Surface *screen, int juste, enigme *en)
{

    SDL_Color textColor = {255, 255, 255};

    SDL_FillRect(screen, NULL, 0x00000);

    if (juste == 1)
    {
        en->ImageResulta = IMG_Load("win.png");
        SDL_BlitSurface(en->ImageResulta, NULL, screen, NULL);
    }
    else
    {
        en->ImageResulta = IMG_Load("lose.png");
        SDL_BlitSurface(en->ImageResulta, NULL, screen, NULL);
    }
    void sauvegarder (perso p,int stage,  char * nomfichier) //; int charger ( personne * p, background *b , char * nomfichier)
{

    FILE* sauv=fopen(nomfichier,"w");
    if (sauv==NULL)
    {
        printf("\n erreur fichier");
    }

    fprintf(sauv,"%d %d %d",p.position.x,p.position.y,stage); //TETBADEL

}
    showText(screen, en->font, textColor, "Press T to try again!", 0, 180);
    SDL_Flip(screen);
}
