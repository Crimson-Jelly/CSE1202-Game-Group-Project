#pragma once
#include <raylib.h>

class player{
    public:
    Vector2 pos;
    Vector2 dir;
    int health;
    float speed=60*5;

    Texture2D player;
    Texture2D gun;
    float scale=2;
    
    void keyboard_movement(float screenW,float screenH);
    void load();
    void draw(Camera2D c);
    void unload();
};
