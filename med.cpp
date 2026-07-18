#include "med.hpp"
#include <cstdlib>

void Medkit::load(){
    texture=LoadTexture("med.png");
}

void Medkit::unload(){
    UnloadTexture(texture);
}

void Medkit::init(float mapWidth,float mapHeight){
    if(active){
        return;
    }

    timer+=GetFrameTime();
    if(timer>=spawnTime){
        timer=0;
        pos.x=(float)GetRandomValue(50,mapWidth);
        pos.y=(float)GetRandomValue(50,mapHeight);
        active=true;
    }
 }

void Medkit::draw(){
    if(active){
        DrawTextureEx(texture,{pos.x,pos.y},0,scale,WHITE);
    }
}

void Medkit::despawn(Vector2 player_pos,int &player_health){
    if(!active) return;
    float dist=Vector2Distance(player_pos,pos);
    if(dist<texture.width*scale){
        active = false;
        player_health+=heal;
    }
    if(player_health>200) player_health=200;
}