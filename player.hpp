#pragma once
#include <raylib.h>

class player{
    public:
    Vector2 pos;
    int health;

    Texture2D player;
    Texture2D gun;
    float scale=2;
    
    void keyboard_movement(float screenW,float screenH);
    void load();
    void draw(Camera2D c);
    void unload();
};
