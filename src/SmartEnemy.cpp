#include "SmartEnemy.h"
#include "random.h"
#include <math.h>

SmartEnemy::SmartEnemy(int x, int y) : Enemy(x, y), velBase(0)
{
    velBase = RandomRange(2, 5);
}

SmartEnemy::~SmartEnemy()
{
}

void SmartEnemy::Draw(SDL_Renderer *rend)
{
    // enemy rectangle
    SDL_Rect rect = GetRect();

    // set color
    SDL_Color color = GetColor();
    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

    // render player
    SDL_RenderFillRect(rend, &rect);
}

void SmartEnemy::Update(Trail::List &trails, Particle::List &particles, int playerX, int playerY)
{
    applyVelocity();
    followPlayer(playerX, playerY);
    updateTrail(trails);
}

void SmartEnemy::applyVelocity(void)
{
    x += velX;
    y += velY;
}

void SmartEnemy::followPlayer(int x, int y)
{
    int dx = x - this->x;
    int dy = y - this->y;
    double dist = sqrt(dx * dx + dy * dy);
    velX = static_cast<int>(dx * velBase / dist);
    velY = static_cast<int>(dy * velBase / dist);

    // TODO dist can be 0, but i haven't found any division by 0 issues yet...
}

void SmartEnemy::updateTrail(Trail::List &trails)
{
    SDL_Color color = GetColor();
    trails.push_back(new Trail(x, y, GetWidth(), GetHeight(), color.r, color.g, color.b));
}

int SmartEnemy::GetWidth(void) const
{
    return 16;
}

int SmartEnemy::GetHeight(void) const
{
    return 16;
}

Enemy::Type SmartEnemy::GetType(void) const
{
    return Type::Smart;
}

SDL_Rect SmartEnemy::GetRect(void) const
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = GetWidth();
    rect.h = GetHeight();
    return rect;
}

SDL_Color SmartEnemy::GetColor(void) const
{
    return {255, 192, 203, 255};
}
