#pragma once
#include <raylib.h>

class Bullet{
    Vector2 pos;
    Vector2 dir;
    float damage;
    Texture2D bullet;
    float speed;
    int Magazine=10;
    int Temp_magazine=Magazine;


    Bullet();
    void movement();
    ~Bullet();
};