#include <stdio.h>
#include <SDL2/SDL.h>
#include "constants.h"

//
int game_is_running = FALSE;
SDL_Window *window;
SDL_Renderer *renderer;


struct ball {
    float x;
    float y;
    float width;
    float height;
} ball;


void process_input();

int initialize_window(void) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL. \n");
        return FALSE;
    }
    // Initialize Window
    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_BORDERLESS
    );
    // Check if there is an Error creating an SDL window
    if (!window) {
        fprintf(stderr, "Error creating SDL Window.\n");
        return FALSE;
    }

    // Initialize Renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    // check if there is an Error creating an SDL Renderer
    if (!renderer) {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return FALSE;
    }

    return TRUE;
}

void setup(void) {
    ball.x = 20;
    ball.y = 20;
    ball.width = 15;
    ball.height = 15;
}

void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            game_is_running = FALSE;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                game_is_running = FALSE;
            }
            break;
    }
}

void update(void) {
    // up force
    ball.x += .01f;
    // down force
    ball.y += .01f;
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //Draw game objects here

    /**
     *  Draw a rectangle
     */
    SDL_Rect ball_rect = {
            (int)ball.x,
            (int)ball.y,
            (int)ball.width,
            (int)ball.height
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ball_rect);
    //

    SDL_RenderPresent(renderer);
}

void destroy_window(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    game_is_running = initialize_window();

    setup();

    while (game_is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();
    return 0;
}


