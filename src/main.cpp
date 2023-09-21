#include "Player.h"
#include "BasicEnemy.h"
#include "HUD.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

#ifdef DEBUG
    // print cwd
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd))) {
        SDL_Log("Working dir is %s\n", cwd);
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error printing working dir");
    }
#endif

    // init random
    std::srand(std::time(nullptr));

    // init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL because %s\n", SDL_GetError());
        return 3;
    }

    // init window
    SDL_Window *window = SDL_CreateWindow("Squarity", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window because %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // init renderer
    SDL_Renderer *rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!rend) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create renderer because %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 2;
    }

    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);

    // init ttf
    if (TTF_Init() != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize TTF because %s\n", TTF_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 4;
    }

    // player
    Player *player = new Player(400 - Player::WIDTH / 2, 300 - Player::HEIGHT / 2, 255, 255, 255);

    // heads up display
    HUD *hud = new HUD(player);

    // enemies
    Enemy::List enemies;
    enemies.push_back(new BasicEnemy(10, 10));

    // trails
    Trail::List trails;

    bool running = true;
    while (running) {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
                case SDL_QUIT:
                    // stop running on quit
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    player->OnKeyPress(ev.key);
                    if (ev.key.keysym.sym == SDLK_ESCAPE)
                        running = false;
                    break;
                case SDL_KEYUP:
                    player->OnKeyRelease(ev.key);
                    break;
            }
        }

        // update player
        player->Update(enemies, trails);

        // update enemies
        for (auto &enemy : enemies) {
            enemy->Update();
        }

        // update trails
        for (size_t i = 0; i < trails.size(); i++) {
            trails[i]->Update();
            if (trails[i]->GetAlpha() == 0) {
                delete trails[i];
                trails.erase(trails.begin() + i);
            }
        }

        // clear window
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);

        // draw trails
        for (auto &trail : trails) {
            trail->Draw(rend);
        }

        // draw player
        player->Draw(rend);

        // draw enemies
        for (auto &enemy : enemies) {
            enemy->Draw(rend);
        }

        // draw HUD
        hud->Draw(rend);

        // update window and wait for next frame
        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 60);
    }

    // destroy player
    delete player;

    // destroy enemies
    for (auto &enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    // destroy trails
    for (auto &trail : trails) {
        delete trail;
    }
    trails.clear();

    // destroy HUD
    delete hud;

    // destroy SDL stuff
    TTF_Quit();
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}
