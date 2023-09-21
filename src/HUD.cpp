#include "HUD.h"
#include "textrender.h"
#include <string>

HUD::HUD(const Player *player) : player(player), font8(nullptr)
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

    RenderText(rend, rectHealth.x + 4, rectHealth.y + 7, font8, {255, 255, 255, 255}, std::to_string(player->GetHealth()).c_str());
}
