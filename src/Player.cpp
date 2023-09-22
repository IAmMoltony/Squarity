#include "Player.h"
#include "collision.h"
#include "imgload.h"

SDL_Texture *Player::spriteIdle, *Player::spriteLeft, *Player::spriteRight, *Player::spriteUp, *Player::spriteDown,
                   *Player::spriteUpLeft, *Player::spriteUpRight, *Player::spriteDownLeft, *Player::spriteDownRight;

void Player::LoadSprites(SDL_Renderer *rend)
{
#ifdef DEBUG
    SDL_Log("Loading player assets\n");
#endif

    spriteIdle = LoadImage(rend, "./assets/images/player_idle.png");
    spriteLeft = LoadImage(rend, "./assets/images/player_left.png");
    spriteRight = LoadImage(rend, "./assets/images/player_right.png");
    spriteUp = LoadImage(rend, "./assets/images/player_up.png");
    spriteDown = LoadImage(rend, "./assets/images/player_down.png");
    spriteUpLeft = LoadImage(rend, "./assets/images/player_up_left.png");
    spriteUpRight = LoadImage(rend, "./assets/images/player_up_right.png");
    spriteDownLeft = LoadImage(rend, "./assets/images/player_down_left.png");
    spriteDownRight = LoadImage(rend, "./assets/images/player_down_right.png");
}

void Player::UnloadSprites(void)
{
#ifdef DEBUG
    SDL_Log("Unloading player assets\n");
#endif

    SDL_DestroyTexture(spriteIdle);
    SDL_DestroyTexture(spriteLeft);
    SDL_DestroyTexture(spriteRight);
    SDL_DestroyTexture(spriteUp);
    SDL_DestroyTexture(spriteDown);
    SDL_DestroyTexture(spriteUpLeft);
    SDL_DestroyTexture(spriteUpRight);
    SDL_DestroyTexture(spriteDownLeft);
    SDL_DestroyTexture(spriteDownRight);
}

Player::Player(int x, int y, Uint8 colorR, Uint8 colorG, Uint8 colorB) : colorR(colorR), colorG(colorG), colorB(colorB),
                                                                         x(x), y(y), velX(0), velY(0), health(FULL_HEALTH),
                                                                         currentSprite(spriteIdle)
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
    SDL_RenderCopy(rend, currentSprite, nullptr, &rect);
}

void Player::Update(Enemy::List &enemies, Trail::List &trails, SDL_Color &bgColor)
{
    applyVelocity();
    clampPosition();
    checkCollision(enemies, bgColor);
    updateTrail(trails);
    updateSprite();
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

void Player::checkCollision(Enemy::List &enemies, SDL_Color &bgColor)
{
    SDL_Rect rect = GetRect();
    for (auto &enemy : enemies) {
        SDL_Rect enemyRect = enemy->GetRect();
        if (RectIntersects(&rect, &enemyRect)) {
            health -= 5;
            enemy->InvertVelocity();
            bgColor.r = 120;
            bgColor.g = 0;
            bgColor.b = 0;
        }
    }
}

void Player::updateTrail(Trail::List &trails)
{
    trails.push_back(new Trail(x, y, WIDTH, HEIGHT, colorR, colorG, colorB));
}

void Player::updateSprite(void)
{
    if (velX > 0 && velY == 0)
        currentSprite = spriteRight;
    else if (velX < 0 && velY == 0)
        currentSprite = spriteLeft;
    else if (velX == 0 && velY < 0)
        currentSprite = spriteUp;
    else if (velX == 0 && velY > 0)
        currentSprite = spriteDown;
    else if (velX > 0 && velY > 0)
        currentSprite = spriteDownRight;
    else if (velX < 0 && velY > 0)
        currentSprite = spriteDownLeft;
    else if (velX < 0 && velY < 0)
        currentSprite = spriteUpLeft;
    else if (velX > 0 && velY < 0)
        currentSprite = spriteUpRight;
    else
        currentSprite = spriteIdle;
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
