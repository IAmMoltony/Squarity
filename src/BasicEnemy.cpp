#include "BasicEnemy.h"
#include <cstdlib>

BasicEnemy::BasicEnemy(int x, int y) : Enemy(x, y)
{
    initVelocity();
}

void BasicEnemy::initVelocity(void)
{
    // -5 or 5 at random for both x and y velocity
    velX = (std::rand() % 2) ? 5 : -5;
    velY = (std::rand() % 2) ? 5 : -5;
}

void BasicEnemy::Draw(SDL_Renderer *rend)
{
    // enemy rectangle
    SDL_Rect rect = GetRect();

    // set color
    SDL_Color color = GetColor();
    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

    // render player
    SDL_RenderFillRect(rend, &rect);
}

void BasicEnemy::Update(Trail::List &trails, Particle::List &particles, int playerX, int playerY)
{
    // player X and Y are not needed
    (void)playerX;
    (void)playerY;

    applyVelocity();
    checkBounds(particles);
    updateTrail(trails);
}

void BasicEnemy::applyVelocity(void)
{
    x += velX;
    y += velY;
}

void BasicEnemy::checkBounds(Particle::List &particles)
{
    bool hitBounds = false;
    if (x < 0 || x > 800 - GetWidth()) {
        velX *= -1;
        hitBounds = true;
    }
    if (y < 0 || y > 600 - GetHeight()) {
        velY *= -1;
        hitBounds = true;
    }

    if (hitBounds) {
        Particle::Spawn(particles, 7, x, y, 5, -3, 3, GetColor());
    }
}

void BasicEnemy::updateTrail(Trail::List &trails)
{
    SDL_Color color = GetColor();
    trails.push_back(new Trail(x, y, GetWidth(), GetHeight(), color.r, color.g, color.b));
}

int BasicEnemy::GetWidth(void) const
{
    return 16;
}

int BasicEnemy::GetHeight(void) const
{
    return 16;
}

Enemy::Type BasicEnemy::GetType(void) const
{
    return Enemy::Type::Basic;
}

SDL_Rect BasicEnemy::GetRect(void) const
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = GetWidth();
    rect.h = GetHeight();
    return rect;
}

SDL_Color BasicEnemy::GetColor(void) const
{
    SDL_Color color;
    color.r = 255;
    color.g = 0;
    color.b = 0;
    color.a = 255;
    return color;
}
