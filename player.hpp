#pragma once
#include <raylib.h>

class player{
    public:
    Vector2 pos;
    Vector2 dir;
    int health;
    float speed=60*5;
    bool alive=true;

    Texture2D player;
    Texture2D gun;
    Texture2D gun_2;
    
    void keyboard_movement(float screenW,float screenH);
    void load();
    void draw(Vector2 mouse_pos);
    void unload();
};
