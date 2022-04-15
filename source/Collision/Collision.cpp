#include "Collision.h"

Collision* Collision::s_Collision = nullptr;


bool Collision::check_Collision(SDL_Rect a, SDL_Rect b)
{
    return (a.x < b.x + b.w) && (a.x + a.w > b.x) && (a.y < b.y + b.h) && (a.y + a.h > b.y);
}
