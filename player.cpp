#include "player.hpp"
#include <cmath>

void player::keyboard_movement(float screenW,float screenH){
    if(IsKeyDown(KEY_W) && pos.y>25){pos.y-=5;}
    if(IsKeyDown(KEY_S) && pos.y<screenH-150){pos.y+=5;}
    if(IsKeyDown(KEY_A) && pos.x>25){pos.x-=5;}
    if(IsKeyDown(KEY_D) && pos.x<screenW-170){pos.x+=5;}
}

void player::load(){
    player=LoadTexture("player.png");
    gun=LoadTexture("gun.png");
    }

void player::draw(Camera2D c){
    Vector2 mouse=GetScreenToWorld2D(GetMousePosition(), c);
    float rotation=atan2(mouse.y-(pos.y+player.height/2),mouse.x-(pos.x+player.width/2))*RAD2DEG;
    Rectangle src={0,0,(float)player.width,(float)player.height};
    Rectangle dest={pos.x+36,pos.y+32,player.width*scale,player.height*scale};
    DrawTextureEx(player,pos,0,scale,WHITE);
    DrawTexturePro(gun,src,dest,{0,12},rotation,WHITE);
}
void player::unload(){
    UnloadTexture(player);
    UnloadTexture(gun);
}