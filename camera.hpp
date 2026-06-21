#pragma once 
#include <raylib.h>

class camera{
    public:
    Camera2D camera={};
    void init(Vector2 p_pos);
    void movement(Vector2 p_pos,float w,float h);
};
