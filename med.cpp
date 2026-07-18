#include "med.hpp"
#include <cstdlib>

Medkit::Medkit(){
    active=false;
    timer=0.0f;
    spawnTime=20.0f;
    pos={0,0};
}
void Medkit::load(){
    texture=LoadTexture("med.png");
}
void Medkit::unload(){
    UnloadTexture(texture);
}
void Medkit::update(float mapWidth,float mapHeight){
    if(active){
        return;
    }
    timer+=GetFrameTime();
    if(timer>=spawnTime){
        timer=0;
        pos.x=50+rand()%((int)mapWidth-100);
        pos.y=50+rand()%((int)mapHeight-100);
        active=true;
    }
}
void Medkit::draw(){
    if(active){
        DrawTexture(texture,pos.x,pos.y,WHITE);
    }
}
Rectangle Medkit::getRect(){
    return Rectangle{pos.x,pos.y,(float)texture.width,(float)texture.height};
}
void Medkit::despawn(){
    active = false;
}