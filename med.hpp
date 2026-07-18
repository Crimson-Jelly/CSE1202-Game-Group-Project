#pragma once
#include <raylib.h>
class Medkit{
public:
    Vector2 pos;
    bool active;
    float timer;
    float spawnTime;
    Texture2D texture;
    Medkit();
    void load();
    void unload();
    void update(float mapWidth, float mapHeight);
    void draw();
    Rectangle getRect();
    void despawn();
};