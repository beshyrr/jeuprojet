#ifndef ENIGME
#define ENIGME

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

typedef struct
{
    SDL_Surface *SpriteSheet;
    SDL_Rect pos;
    SDL_Rect Clips[5];
    int frames;
    int ClipLoaded;
} animation;

typedef struct
{
    SDL_Surface *ImageResulta;

    SDL_Surface *question;
    SDL_Rect PosQuestion;

    SDL_Surface *background;
    TTF_Font *font;

    SDL_Surface *reponses[4];
    SDL_Rect PosReponse[4];

    int reponse;
    animation animation;
} enigme;

void init_enigme(enigme *e);
void generate_afficher(SDL_Surface *screen, enigme *e, int *alea);
int resolution(SDL_Surface *screen, enigme e, int *loop, int startTime);
void afficher_resultat(SDL_Surface *screen, int r, enigme *en);
void showText(SDL_Surface *surface, TTF_Font *font, SDL_Color color, char *text, int x, int y);
#endif /* ENIGME */
