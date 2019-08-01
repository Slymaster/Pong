#include "lib.h"

Paddle *createPaddle(SDL_Renderer *rend, SDL_Window *window)
{
    Paddle *paddle;
    paddle = malloc(sizeof(Paddle));

    if(paddle == NULL)
    {
        printf("Error creating paddle struct\n");
        return NULL;
    }

    paddle->paddleSurface = IMG_Load("asset/paddle_sprite.png");

    if(!paddle->paddleSurface)
    {
        printf("error creating surface paddle\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }

    paddle->paddleTexture = SDL_CreateTextureFromSurface(rend, paddle->paddleSurface);

    SDL_FreeSurface(paddle->paddleSurface);

    if (!paddle->paddleTexture)
    {

        printf("error creating texture player: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }

    paddle->paddleRect.x = 100;
    paddle->paddleRect.y = 800/2;

    return paddle;
}
