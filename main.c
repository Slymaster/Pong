#include "lib.h"
#define LEN_MAX 80

int displayMenue()
{
    char *Ip;
    int port;

    printf("To join the party give the ip adresse: ");
    scanf("%s", Ip);

    printf("\n");

    printf("Give the port: ");
    scanf("%d", &port);

    /*Uint32 flags = SDL_RENDERER_ACCELERATED;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Pong-client",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, flags);

    if (!rend)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    //void Redraw();
    char *ipText;
    char *portText;
    SDL_bool done = SDL_FALSE; 
    Sint32 cursor, select;
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    char rep[LEN_MAX + 1] = {0};
	size_t len = 0;
	SDL_Event event;
	SDL_bool quit = SDL_FALSE;
	while(!quit)
	{
		SDL_bool has_type = SDL_FALSE;
		SDL_WaitEvent(&event);
		if(event.type == SDL_QUIT)
			quit = SDL_TRUE;
		else if( event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.sym == SDLK_BACKSPACE && len)
			{
				rep[len - 1] = 0;
				len--;
				has_type = SDL_TRUE;
			}
			if(event.key.keysym.sym == SDLK_v && (SDL_GetModState() & KMOD_CTRL) && SDL_HasClipboardText())
			{
				char *tmp = SDL_GetClipboardText();
				size_t l = strlen(tmp);
				size_t l_copy = len + l < LEN_MAX ? l : LEN_MAX - len;
				strncpy(rep + len, tmp, l_copy);
				len += l_copy;
				SDL_free(tmp);
				has_type = SDL_TRUE;
			}
			if(event.key.keysym.sym == SDLK_c && (SDL_GetModState() & KMOD_CTRL))
				SDL_SetClipboardText(rep);
		}
		else if(event.type == SDL_TEXTINPUT)
		{
			size_t l = strlen(event.text.text);
			size_t l_copy = len + l < LEN_MAX ? l : LEN_MAX - len;
			strncpy(rep + len, event.text.text, l_copy);
			len += l_copy;
			has_type = SDL_TRUE;
		}
		if(has_type)
			puts(rep);
	}*/
}

int main()
{
    
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    pthread_t serverThread;

    pthread_create(&serverThread, NULL, launchServer, NULL);

    sleep(1);



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
    int sockClient = startClient();
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
                        funcClient(sockClient);
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
        //displayMenue();
        SDL_DestroyWindow(win);
        SDL_Quit();  
}