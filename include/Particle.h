#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL2/SDL.h>
#include <vector>

class Particle
{
public:
    typedef Particle *Pointer;
    typedef std::vector<Pointer> List;

    static void Spawn(List &particles, int n, int x, int y, int size, int minVel, int maxVel, SDL_Color color);

    Particle(int x, int y, int size, int velX, int velY, SDL_Color color);
    ~Particle();

    void Draw(SDL_Renderer *rend);
    void Update(void);

    int GetAlpha(void) const;

private:
    void applyVelocity(void);
    void updateAlpha(void);

    int x, y, size, velX, velY, r, g, b, a;
};

#endif // PARTICLE_H
