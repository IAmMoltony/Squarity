#include "HUD.h"
#include "textrender.h"
#include <string>

HUD::HUD(const Player *player, int *score, int *level, int *nextLevelScore) : player(player), score(score), level(level), nextLevelScore(nextLevelScore), font8(nullptr)
{
    font8 = TTF_OpenFont("./assets/fonts/font.ttf", 8);
    if (!font8) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Can't open font because %s\n", strerror(errno));
    }
}

HUD::~HUD()
{
    TTF_CloseFont(font8);
}

void HUD::Draw(SDL_Renderer *rend)
{
    SDL_Rect rectHealth;
    rectHealth.x = 15;
    rectHealth.y = 600 - 38;
    rectHealth.w = player->GetHealth();
    rectHealth.h = 23;

    SDL_Rect rectHealthBorder = rectHealth;
    rectHealthBorder.w = Player::FULL_HEALTH;

    SDL_SetRenderDrawColor(rend, 0, 200, 0, 128);
    SDL_RenderFillRect(rend, &rectHealth);

    SDL_SetRenderDrawColor(rend, 0, 200, 200, 128);
    SDL_RenderDrawRect(rend, &rectHealthBorder);

    // health text
    RenderText(rend, rectHealth.x + 4, rectHealth.y + 7, font8, {255, 255, 255, 255},
               std::string(std::to_string(player->GetHealth()) + "/" + std::to_string(Player::FULL_HEALTH)).c_str());

    // score text
    RenderText(rend, rectHealth.x + 4, rectHealth.y - 10, font8, {255, 255, 255, 255},
               std::string("Score: " + std::to_string(*score) + '/' + std::to_string(*nextLevelScore)).c_str());

    // level text
    RenderText(rend, rectHealth.x + 4, rectHealth.y - 20, font8, {255, 255, 255, 255},
               std::string("Level: " + std::to_string(*level)).c_str());
}
