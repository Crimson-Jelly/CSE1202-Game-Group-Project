#include "med.hpp"
#include <cstdlib>

Medikit::Medikit(){
    active = false;
    timer = 0.0f;
    spawnTime = 20.0f;
    pos = {0,0};
}
void Medikit::load(){
    texture = LoadTexture("med.png");
}
void Medikit::unload(){
    UnloadTexture(texture);
}
void Medikit::update(float mapWidth,float mapHeight){
    if(active){
        return;
    }
    timer += GetFrameTime();
    if(timer >= spawnTime){
        timer = 0;
        pos.x = 50 + rand()%((int)mapWidth-100);
        pos.y = 50 + rand()%((int)mapHeight-100);
        active = true;
    }
}
void Medikit::draw(){
    if(active){
        DrawTexture(texture,pos.x,pos.y,WHITE);
    }
}
Rectangle Medikit::getRect(){
    return Rectangle{
        pos.x,
        pos.y,
        (float)texture.width,
        (float)texture.height
    };
}
void Medikit::despawn(){
    active = false;
}