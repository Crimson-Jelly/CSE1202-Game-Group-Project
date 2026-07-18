#pragma once
#include <raylib.h>
#include <raymath.h>

class Medkit{
public:
    Vector2 pos;
    bool active=false;
    float timer=0;
    float spawnTime=10;
    Texture2D texture;
    float scale=2.5;
    int heal=15;

    void load();
    void unload();
    void init(float mapWidth, float mapHeight);
    void draw();
    void despawn(Vector2 player_pos,int &player_health);
};