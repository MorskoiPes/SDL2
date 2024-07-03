#include <iostream>
#include <vector>
#include <map>


#define SDL_MAIN_HANDLED
#include <SDL.h>



const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int LENGHT = 20;
const int WIDTH = 10;

SDL_Window* win = NULL;
SDL_Surface* scr = NULL;
SDL_Surface* john = NULL;
SDL_Renderer* ren = NULL;



int quit() {
    //SDL_FreeSurface(john);

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

    win = SDL_CreateWindow("Source", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS);
    if (win == NULL) {
        std::cout << "Can't create window: " << SDL_GetError() << std::endl;
        system("pause");
        return 1;
    }

    ren = SDL_CreateRenderer(win, 1, SDL_RENDERER_ACCELERATED);

    if (ren == NULL) {
        std::cout << "Can't create render:" << SDL_GetError() << std::endl;
        system("pause");
        return quit();
    }

    scr = SDL_GetWindowSurface(win);

    return 0;
}

void quadrat(int* x, int* y) {


    SDL_Rect fillRect = { *x - (WIDTH / 2) , *y - (LENGHT / 2) , WIDTH , LENGHT };

    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);

    SDL_RenderFillRect(ren, &fillRect);

    
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

class Quadrats {
public:
    int X_position = 0;
    int Y_position = 0;

};


int main(int argc, char** args) {
    if (init() == 1) {
        quit();
        return 1;

    }

    /*if (load() == 1) {
        quit();
        return 1;
    }*/

    int count = 0;

    bool run = true;
    SDL_Event e;

    int x = 50;
    int y = 50;

    std::vector<std::pair<int, int>> position_member;
    std::pair<int, int> x_y_position;
    SDL_Rect bg;
    bg.w = SCREEN_WIDTH;
    bg.h = SCREEN_HEIGHT;
    bg.x = x;
    bg.y = y;

    SDL_RenderClear(ren);




    while (run) {

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
        SDL_RenderClear(ren);

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
                if (e.key.keysym.sym == SDLK_1) {
                    SDL_SetWindowSize(win, 640, 480);
                    SDL_SetWindowPosition(win, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                }
                if (e.key.keysym.sym == SDLK_2) {
                    SDL_SetWindowSize(win, 1080, 720);
                    SDL_SetWindowPosition(win, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                }
            }

            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == 1) {
                count += 1;

                x_y_position.first = e.motion.x;
                x_y_position.second = e.motion.y;

                position_member.push_back(x_y_position);

            }
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == 3) {

                count -= 1;
                int mouse_p_x = e.motion.x;
                int mouse_p_y = e.motion.y;
                int g = 0;

                //for(std::pair<int, int> i : position_member)

                for (int g = 0; g < position_member.size();g++) {
                    
                    int x_p_min = position_member[g].first - (WIDTH / 2), y_p_min = position_member[g].second - (LENGHT / 2), x_p_max = position_member[g].first + (WIDTH / 2), y_p_max = position_member[g].second + (LENGHT / 2);
                    /*
                    std::cout << mouse_p_x << "\t" << mouse_p_y << std::endl;
                    std::cout << x_p_min << "\t" << x_p_max << std::endl;
                    std::cout << y_p_min << "\t" << y_p_max << "\n" << std::endl;
                    */
                    if (x_p_min <= mouse_p_x && mouse_p_x <= x_p_max && y_p_min <= mouse_p_y && mouse_p_y <= y_p_max) {

                        //std::cout << i.first << "\t" << i.second << std::endl;
                        //std::cout << e.motion.x << "\t" << e.motion.y << std::endl;

                        position_member.erase(position_member.begin() + g);

                    }
                    
                }
            }
        }

        bg.x = x;
        bg.y = y;

        for (std::pair<int, int> i : position_member) {

            quadrat(&i.first, &i.second);

        }



        //SDL_FillRect(scr, NULL, SDL_MapRGB(scr->format, 255, 255, 255));
        //SDL_BlitScaled(john, NULL, scr, &bg);

        SDL_UpdateWindowSurface(win);
        SDL_RenderPresent(ren);
    }

    quit();
}