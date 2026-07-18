#pragma once
#include <raylib.h>
class Medikit{
public:
    Vector2 pos;
    bool active;
    float timer;
    float spawnTime;
    Texture2D texture;
    Medikit();
    void load();
    void unload();
    void update(float mapWidth, float mapHeight);
    void draw();
    Rectangle getRect();
    void despawn();
};