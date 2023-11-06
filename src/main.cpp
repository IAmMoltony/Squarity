#include "Player.h"
#include "BasicEnemy.h"
#include "FastEnemy.h"
#include "SmartEnemy.h"
#include "EnemySpawner.h"
#include "HUD.h"
#include "Particle.h"
#include "random.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#ifdef WIN32
#include <Windows.h>
#endif // WIN32

static SDL_Window *_window = nullptr;
static SDL_Renderer *_rend = nullptr;

static int _score = 0;
static int _level = 1;
static int _nextLevelScore = 1000;
static Player *_player = nullptr;
static HUD *_hud = nullptr;
static EnemySpawner *_enemySpawner = nullptr;
static Enemy::List _enemies;
static Trail::List _trails;
static Particle::List _particles;
static SDL_Color _bgColor;

static int _Init(void)
{
#ifdef DEBUG
    SDL_Log("Initializing\n");

    // print cwd
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd))) {
        SDL_Log("Working dir is %s\n", cwd);
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error printing working dir\n");
    }
#endif

    // init random
    RandomInit();

    // init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL because %s\n", SDL_GetError());
        return 3;
    }

    // init window
    _window = SDL_CreateWindow("Squarity", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (!_window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window because %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // init renderer
    _rend = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_rend) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create renderer because %s\n", SDL_GetError());
        SDL_DestroyWindow(_window);
        SDL_Quit();
        return 2;
    }

    SDL_SetRenderDrawBlendMode(_rend, SDL_BLENDMODE_BLEND);

    // init ttf
    if (TTF_Init() != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize TTF because %s\n", TTF_GetError());
        SDL_DestroyRenderer(_rend);
        SDL_DestroyWindow(_window);
        SDL_Quit();
        return 4;
    }

    // init mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize mixer because %s\n", Mix_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(_rend);
        SDL_DestroyWindow(_window);
        SDL_Quit();
        return 5;
    }

    // score
    _score = 0;

    // player
    _player = new Player(400 - Player::WIDTH / 2, 300 - Player::HEIGHT / 2, 255, 255, 255);

    // heads up display
    _hud = new HUD(_player, &_score, &_level, &_nextLevelScore);

    // bg color
    _bgColor = {0, 0, 0, 255};

    // init enemy spawner
    _enemySpawner = new EnemySpawner(_enemies);

    // spawn some enemies
    _enemySpawner->SpawnEnemies(3);

    // load player stuff
    Player::LoadSprites(_rend);
    Player::LoadSounds();

    return 0;
}

static void _Destroy(void)
{
#ifdef DEBUG
    SDL_Log("Destroying\n");
#endif

    // unload player stuff
    Player::UnloadSprites();
    Player::UnloadSounds();

    // destroy player
    delete _player;

    // destroy enemy spawner
    delete _enemySpawner;

    // destroy enemies
    for (auto &enemy : _enemies) {
        delete enemy;
    }
    _enemies.clear();

    // destroy trails
    for (auto &trail : _trails) {
        delete trail;
    }
    _trails.clear();

    // destroy particles
    for (auto &particle : _particles) {
        delete particle;
    }
    _particles.clear();

    // destroy HUD
    delete _hud;

    // destroy SDL stuff
    Mix_Quit();
    TTF_Quit();
    SDL_DestroyRenderer(_rend);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

static void _PollEvents(bool &running)
{
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        switch (ev.type) {
            case SDL_QUIT:
                // stop running on quit
                running = false;
                break;
            case SDL_KEYDOWN:
                _player->OnKeyPress(ev.key);
                if (ev.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
                break;
            case SDL_KEYUP:
                _player->OnKeyRelease(ev.key);
                break;
        }
    }
}

static void _NextLevel(void)
{
    _nextLevelScore += 1500;
    _level++;

    // spawn enemies
    _enemySpawner->SpawnEnemies(1);

    // set bg color
    _bgColor = {0, 128, 128, 255};
}

static void _Update(void)
{
    _score++;

    if (_score == _nextLevelScore) {
        // next level
        _NextLevel();
    }

    // update player
    _player->Update(_enemies, _trails, _particles, _bgColor);

    // update enemies
    for (auto &enemy : _enemies) {
        enemy->Update(_trails, _particles, _player->GetX(), _player->GetY());
    }

    // update trails
    for (size_t i = 0; i < _trails.size(); i++) {
        _trails[i]->Update();
        if (_trails[i]->GetAlpha() == 0) {
            delete _trails[i];
            _trails.erase(_trails.begin() + i);
        }
    }

    // update particles
    for (size_t i = 0; i < _particles.size(); i++) {
        _particles[i]->Update();
        if (_particles[i]->GetAlpha() == 0) {
            delete _particles[i];
            _particles.erase(_particles.begin() + i);
        }
    }

    // update bg color
    for (int i = 0; i < 3; i++) {
        if ((int)_bgColor.r - 1 >= 0)
            _bgColor.r--;
        if ((int)_bgColor.g - 1 >= 0)
            _bgColor.g--;
        if ((int)_bgColor.b - 1 >= 0)
            _bgColor.b--;
    }
}

static void _Draw(void)
{
    // clear window
    SDL_SetRenderDrawColor(_rend, _bgColor.r, _bgColor.g, _bgColor.b, 255);
    SDL_RenderClear(_rend);

    // draw trails
    for (auto &trail : _trails) {
        trail->Draw(_rend);
    }

    // draw particles
    for (auto &particle : _particles) {
        particle->Draw(_rend);
    }

    // draw player
    _player->Draw(_rend);

    // draw enemies
    for (auto &enemy : _enemies) {
        enemy->Draw(_rend);
    }

    // draw HUD
    _hud->Draw(_rend);

    // update window and wait for next frame
    SDL_RenderPresent(_rend);
}

static void _Run(void)
{
    bool running = true;
    while (running) {
        _PollEvents(running);
        _Update();
        _Draw();
    }
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    int initResult = _Init();
    if (initResult)
        return initResult;

    _Run();
    _Destroy();

    return 0;
}

#ifdef WIN32
int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow)
{
    (void)instance;
    (void)prevInstance;
    (void)cmdLine;
    (void)cmdShow;
    main(__argc, __argv);
    return 0;
}
#endif // WIN32
