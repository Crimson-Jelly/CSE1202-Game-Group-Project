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
    
    void keyboard_movement(float screenW,float screenH);
    void load();
    void draw(Vector2 mouse_pos);
    void unload();
};
