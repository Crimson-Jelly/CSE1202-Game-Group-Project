#include "player.hpp"
#include <raymath.h>
#include <cmath>
#include "asset_loader.hpp"
void player::keyboard_movement(float screenW,float screenH){  
    float dt=GetFrameTime();
    dir={0,0};
    if(IsKeyDown(KEY_W) && pos.y>25){dir.y=-1.0f;}
    if(IsKeyDown(KEY_S) && pos.y<screenH-150){dir.y=1.0f;}
    if(IsKeyDown(KEY_A) && pos.x>25){dir.x=-1.0f;}
    if(IsKeyDown(KEY_D) && pos.x<screenW-170){dir.x=1.0f;}

    if(dir.x!=0 || dir.y!=0){
        dir=Vector2Normalize(dir);
        pos.x+=dir.x*speed*dt;
        pos.y+=dir.y*speed*dt;
    }
    else{
        pos.x+=dir.x*speed*dt;
        pos.y+=dir.y*speed*dt;
    }
}

void player::draw(Vector2 mouse_pos){
    float rotation=atan2(mouse_pos.y-(pos.y+assets.player.height/2),mouse_pos.x-(pos.x+assets.player.width/2))*RAD2DEG;
    Rectangle src={0,0,(float)assets.gun.width,(float)assets.gun.height};
    Rectangle dest={pos.x+18*scale,pos.y+18*scale,assets.gun.width*scale,assets.gun.height*scale};
    DrawTextureEx(assets.player,pos,0,scale,WHITE);
    DrawTexturePro(assets.gun,src,dest,{0,6*scale},rotation,WHITE);
}
