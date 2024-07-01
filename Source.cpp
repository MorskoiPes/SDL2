#include <iostream>


#define SDL_MAIN_HANDLED
#include <SDL.h>



const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* win = NULL;
SDL_Surface* scr = NULL;
SDL_Surface* john = NULL;
SDL_Renderer* ren = NULL;

int quit() {
    SDL_FreeSurface(john);

    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}

int init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Can't init: " << SDL_GetError() << std::endl;
        system("pause");
        return 1;
    }

    win = SDL_CreateWindow("Source", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (win == NULL) {
        std::cout << "Can't create window: " << SDL_GetError() << std::endl;
        system("pause");
        return 1;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    if (ren == NULL) {
        std::cout << "Can't create render:" << SDL_GetError() << std::endl;
        system("pause");
        return quit();
    }

    scr = SDL_GetWindowSurface(win);

    return 0;
}

int load() {
    john = SDL_LoadBMP("john.bmp");
    
    if (john == NULL) {
        std::cout << "Can't load image: " << SDL_GetError() << std::endl;
        system("pause");
        return 1;
    }

    return 0;
}


int main(int argc, char** args) {
    if (init() == 1) {
        quit();
        return 1;

    }

    if (load() == 1) {
        quit();
        return 1;
    }

    bool run = true;
    SDL_Event e;

    int x = 0;
    int y = 0;

    SDL_Rect bg;
    bg.w = SCREEN_WIDTH;
    bg.h = SCREEN_HEIGHT;
    bg.x = x;
    bg.y = y;


    while (run) {
        while (SDL_PollEvent(&e) != NULL) {
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    run = false;
                }
   
            }

            if (e.type == SDL_QUIT) {
                run = false;
            }

            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_UP) {
                    y -= 1;
                }
                if (e.key.keysym.sym == SDLK_DOWN) {
                    y += 1;
                }
                if (e.key.keysym.sym == SDLK_RIGHT) {
                    x += 1;
                }
                if (e.key.keysym.sym == SDLK_LEFT) {
                    x -= 1;
                }
            }
        }
        bg.x = x;
        bg.y = y;

        SDL_FillRect(scr, NULL, SDL_MapRGB(scr->format, 255, 255, 255));

        SDL_BlitScaled(john, NULL, scr, &bg);

        SDL_UpdateWindowSurface(win);
    }

    SDL_Rect fillRect = { SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    SDL_SetRenderDrawColor(ren, 255,0,0,255);
    SDL_RenderFillRect(ren,&fillRect);

    quit();
}