#pragma once
#include <raylib.h>

class Enemy{
    public:
    Vector2 pos;
    float speed=2;
    int health = 100;
    float atk_speed=6;
    float shoot_timer=0;
    float spawntime=3;
    bool alive=true;
    float hitbox=40;
    static Texture2D enemy_texture;

    Enemy(float mapWidth,float mapHeight);
    static void load();
    static void unload();
    void movement(Vector2 playerPos);
    void draw(Vector2 playerPos);
};
