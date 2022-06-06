#ifndef __VHELPERS__
#define __VHELPERS__
struct HitInfo
{
    int x;
};

struct FRect {
    float w;
    float h;
    float x;
    float y;
};

bool checkCollision( FRect a, FRect b, HitInfo* hit_info);


#endif