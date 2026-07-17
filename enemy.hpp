#pragma once
#include <raylib.h>

class Enemy{
    public:
    Vector2 pos;
    float speed=2;
    float damage;
    int health=100;
    float atk_speed;
    bool alive=true;
    static Texture2D enemy_texture;

    Enemy(float mapWidth,float mapHeight);
    static void load();
    static void unload();
    void update(Vector2 playerPos);
    void draw(Vector2 playerPos);
};
