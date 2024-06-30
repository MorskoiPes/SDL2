#include <iostream>


#define SDL_MAIN_HANDLED
#include <SDL.h>



const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* win = NULL;
SDL_Surface* scr = NULL;
SDL_Surface* john = NULL;

int init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Can't init: " << SDL_GetError() << std::endl;
        system("pause");
        return 1;
    }

    win = SDL_CreateWindow("Source", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        std::cout << "Can't create window: " << SDL_GetError() << std::endl;
        system("pause");
        return 1;
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

int quit() {
    SDL_FreeSurface(john);

    SDL_DestroyWindow(win);

    SDL_Quit();

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

    SDL_Rect bg_flower;
    bg_flower.w = SCREEN_WIDTH;
    bg_flower.h = SCREEN_HEIGHT;
    bg_flower.x = 0;
    bg_flower.y = 0;


    SDL_BlitScaled(john, NULL, scr, &bg_flower);

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
        r.x = x;
        r.y = y;

        SDL_FillRect(scr, NULL, SDL_MapRGB(scr->format, 255, 255, 255));

        SDL_BlitSurface(john, NULL, scr, &r);

        SDL_UpdateWindowSurface(win);
    }

    quit();
}