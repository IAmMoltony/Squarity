#ifndef TRAIL_H
#define TRAIL_H

#include <SDL2/SDL.h>
#include <vector>

class Trail
{
public:
    typedef Trail *Pointer;
    typedef std::vector<Pointer> List;

    Trail(int x, int y, int w, int h, Uint8 colorR, Uint8 colorG, Uint8 colorB);
    ~Trail();

    void Draw(SDL_Renderer *rend);
    void Update(void);

    Uint8 GetAlpha(void);

private:
    int x, y, w, h, a;
    Uint8 r, g, b;
};

#endif // TRAIL_H
