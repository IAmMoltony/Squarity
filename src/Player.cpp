#include "Player.h"
#include "collision.h"

Player::Player(int x, int y, Uint8 colorR, Uint8 colorG, Uint8 colorB) : colorR(colorR), colorG(colorG), colorB(colorB),
                                                                         x(x), y(y), velX(0), velY(0), health(FULL_HEALTH)
{
}

Player::~Player()
{
}

void Player::Draw(SDL_Renderer *rend)
{
    // player rectangle
    SDL_Rect rect = GetRect();

    // set color
    SDL_SetRenderDrawColor(rend, colorR, colorG, colorB, 255);

    // render player
    SDL_RenderFillRect(rend, &rect);
}

void Player::Update(Enemy::List &enemies, Trail::List &trails)
{
    applyVelocity();
    clampPosition();
    checkCollision(enemies);
    updateTrail(trails);
}

void Player::applyVelocity(void)
{
    x += velX;
    y += velY;
}

void Player::clampPosition(void)
{
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    if (x > 800 - WIDTH)
        x = 800 - WIDTH;
    if (y > 600 - HEIGHT)
        y = 600 - HEIGHT;
}

void Player::checkCollision(Enemy::List &enemies)
{
    SDL_Rect rect = GetRect();
    for (auto &enemy : enemies) {
        SDL_Rect enemyRect = enemy->GetRect();
        if (RectIntersects(&rect, &enemyRect)) {
            health--;
        }
    }
}

void Player::updateTrail(Trail::List &trails)
{
    trails.push_back(new Trail(x, y, WIDTH, HEIGHT, colorR, colorG, colorB));
}

void Player::OnKeyPress(SDL_KeyboardEvent ev)
{
    SDL_Keycode code = ev.keysym.sym;
    switch (code) {
        case SDLK_LEFT:
        case SDLK_a:
            // go to left
            velX = -5;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            // go to right
            velX = 5;
            break;
        case SDLK_UP:
        case SDLK_w:
            // go to up
            velY = -5;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            // go to down
            velY = 5;
            break;
        default:
            break;
    }
}

void Player::OnKeyRelease(SDL_KeyboardEvent ev)
{
    SDL_Keycode code = ev.keysym.sym;
    switch (code) {
        case SDLK_LEFT:
        case SDLK_RIGHT:
        case SDLK_a:
        case SDLK_d:
            velX = 0;
            break;
        case SDLK_UP:
        case SDLK_DOWN:
        case SDLK_w:
        case SDLK_s:
            velY = 0;
            break;
    }
}

SDL_Rect Player::GetRect(void) const
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = WIDTH;
    rect.h = HEIGHT;
    return rect;
}

int Player::GetHealth(void) const
{
    return health;
}
