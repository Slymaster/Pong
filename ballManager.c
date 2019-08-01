#include "lib.h"

Ball *createBall(SDL_Renderer *rend , SDL_Window *window)
{
    Ball *ball;
    ball = malloc(sizeof(Ball));

    if(ball == NULL)
    {
       printf("Error creating ball struct\n");
       return NULL; 
    }

    ball->ballSurface = IMG_Load("asset/ball_sprite.png");

    if(!ball->ballSurface)
    {
        printf("error creating ball surface\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }

    ball->ballTexture = SDL_CreateTextureFromSurface(rend, ball->ballSurface);

    SDL_FreeSurface(ball->ballSurface);

    if (!ball->ballTexture)
    {

        printf("error creating texture ball: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }

    ball->ballRect.x = 400;
    ball->ballRect.y = 400;

    return ball;
}