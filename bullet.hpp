#pragma once
#include <raylib.h>
#include <math.h>

class Bullet{
public:
    Vector2 pos;
    Vector2 velocity;
    Vector2 dir;
    static Texture2D bullet_texture;
    int damage = 20;
    
    float speed=12.0f;
    bool active=true;
    float dmg = 20;

    Bullet(Vector2 intpos,Vector2 targetpos);
    void update();
    void draw(Vector2 mouse_pos);
    static void load();
    static void unload();
};
