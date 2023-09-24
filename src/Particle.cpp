#include "Particle.h"
#include "random.h"

Particle::Particle(int x, int y, int size, int velX, int velY, SDL_Color color) : x(x), y(y), size(size), velX(velX), velY(velY), r(color.r), g(color.g), b(color.b), a(255)
{
}

Particle::~Particle()
{
}

void Particle::Spawn(List &particles, int n, int x, int y, int size, int minVel, int maxVel, SDL_Color color)
{
    for (int i = 0; i < n; i++) {
        particles.push_back(new Particle(x, y, size, RandomRange(minVel, maxVel), RandomRange(minVel, maxVel), color));
    }
}

void Particle::Draw(SDL_Renderer *rend)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = size;
    rect.h = size;

    SDL_SetRenderDrawColor(rend, r, g, b, a);
    SDL_RenderFillRect(rend, &rect);
}

void Particle::Update(void)
{
    applyVelocity();
    updateAlpha();
}

void Particle::applyVelocity(void)
{
    x += velX;
    y += velY;
}

void Particle::updateAlpha(void)
{
    a -= 7;
    if (a < 0)
        a = 0;
}

int Particle::GetAlpha(void) const
{
    return a;
}
