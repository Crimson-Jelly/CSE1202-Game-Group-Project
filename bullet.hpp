#pragma once
#include <raylib.h>
#include <math.h>

class Bullet{
    Vector2 pos;
    Vector2 velocity;
    Vector2 dir;
    static Texture2D bullet;

    float speed=12.0f;
    bool active;
    int Magazine=10;
    int Temp_magazine=Magazine;
    float damage;



    Bullet(Vector2 intpos,Vector2 targetpos);
    void update();
    void load();
    void unload();
    void draw(Vector2 mouse_pos);

};