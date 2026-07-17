#pragma once
#include <raylib.h>
#include <math.h>

class Bullet{
    Vector2 pos;
    Vector2 velocity;
    Vector2 dir;
    

    float speed=12.0f;
<<<<<<< HEAD
    bool active=true;
    float damage=40;

=======
    bool active;
    int Magazine=10;
    int Temp_magazine=Magazine;
    float damage;


    public:
>>>>>>> 41e5a09a3fd853368bba42d86b5994c6ae98003c
    Bullet(Vector2 intpos,Vector2 targetpos);
    void update();
    void draw(Vector2 mouse_pos);
<<<<<<< HEAD
};
=======

};
>>>>>>> 41e5a09a3fd853368bba42d86b5994c6ae98003c
