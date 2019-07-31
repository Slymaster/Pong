#ifndef _LIB_H_
#define _LIB_H_

#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>


#define WINDOW_WIDTH (800)
#define WINDOW_HEIGHT (800)


typedef struct 
{
    int x_pos;
    int y_pos;
    SDL_Surface *paddleSurface;
    SDL_Texture *paddleTexture;
    SDL_Rect paddleRect;
}Paddle;



typedef struct 
{
    SDL_Surface *ballSurface;
    SDL_Texture *ballTexture;
    SDL_Rect ballRect;
}Ball;

//Paddle *createPaddle(SDL_Renderer *rend, SDL_Window *window);

#endif
