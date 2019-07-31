#include "lib.h"


/* SDL_bool checkCollision(&rect1, SDL_Rect *rect2)
{
    SDL_bool collision = SDL_HasIntersection(&rect1, &rect2);
    return collision;
}*/

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




int main()
{
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    // Create a function to display the screen 
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Pong",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);

    if (!rend)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    Paddle *player1 = createPaddle(rend, win);
    Paddle *player2 = createPaddle(rend, win);
    Ball *ball = createBall(rend, win);

    SDL_QueryTexture(player1->paddleTexture, NULL, NULL, &player1->paddleRect.w, &player1->paddleRect.h);
    SDL_QueryTexture(player2->paddleTexture, NULL, NULL, &player2->paddleRect.w, &player2->paddleRect.h);
    SDL_QueryTexture(ball->ballTexture, NULL, NULL, &ball->ballRect.w, &ball->ballRect.h);

    player1->paddleRect.w = 20;
    player1->paddleRect.h = 125;

    player2->paddleRect.w = 20;
    player2->paddleRect.h = 125;

    //Paddle2 init position
    player2->paddleRect.x = player1->paddleRect.x + 580;
    

    //game loop:
    int closeFlag = 0;
    int moveTop = 0;
    int moveBottom = moveTop;
    int collideFlag = 0;

     while (closeFlag != 1)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                closeFlag =1;
            break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {

                    case SDL_SCANCODE_UP:
                        if( player1->paddleRect.y > 0)
                        {
                            
                            player1->paddleRect.y -= 10;
                        }else{
                            player1->paddleRect.y = player1->paddleRect.y;
                        }
                        //printf("PAddle position y:%d\n", player1->paddleRect.y);
                    break;

                    case SDL_SCANCODE_DOWN:
                        if( player1->paddleRect.y < 800-(player1->paddleRect.h))
                        {
                            player1->paddleRect.y += 10;
                            //printf("PAddle position y:%d\n", player1->paddleRect.y);
                        }else{
                            player1->paddleRect.y = player1->paddleRect.y;
                        } 
                    break;

                    case SDL_SCANCODE_T:
                        if( player2->paddleRect.y > 0)
                        {
                            
                            player2->paddleRect.y -= 10;
                        }else{
                            player2->paddleRect.y = player2->paddleRect.y;
                        }
                    break;

                    case SDL_SCANCODE_B:
                        if( player2->paddleRect.y < 800-(player2->paddleRect.h))
                        {
                            player2->paddleRect.y += 80;
                            //printf("PAddle position y:%d\n", player1->paddleRect.y);
                        }else{
                            player2->paddleRect.y = player2->paddleRect.y;
                        } 
                    break;

                    case SDL_SCANCODE_S:
                        if(SDL_HasIntersection(&player1->paddleRect,&ball->ballRect))
                        {
                            collideFlag = 1;
                        }else{
                            ball->ballRect.x -= 5;
                        }
                    break;
            
                }
                
            break;

        }

        if(collideFlag ==1)
        {
            ball->ballRect.x = ball->ballRect.x + 2*player1->paddleRect.w;
        }


        SDL_RenderClear(rend);
        
        SDL_RenderCopy(rend, player1->paddleTexture, NULL, &player1->paddleRect);
        SDL_RenderCopy(rend, player2->paddleTexture, NULL, &player2->paddleRect);
        SDL_RenderCopy(rend, ball->ballTexture, NULL, &ball->ballRect);
        SDL_RenderPresent(rend);
        collideFlag = 0;
        SDL_Delay(1000/60);
    }
        SDL_DestroyWindow(win);
        SDL_Quit();  
}