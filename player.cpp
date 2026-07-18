#include "global.hpp"
#include "player.hpp"
#include "asset_loader.hpp"
#include "raylib.h"
#include "raymath.h"
#include <cmath>

void player::keyboard_movement(float screenW,float screenH){  
    float dt=GetFrameTime();
    dir={0,0};
    if((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && pos.y>25){pos.y-=5;}
    if((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) && pos.y<screenH-150){pos.y+=5;}
    if((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && pos.x>25){pos.x-=5;}
    if((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && pos.x<screenW-170){pos.x+=5;}
    if(dir.x!=0 || dir.y!=0){
        dir=Vector2Normalize(dir);
        pos.x+=dir.x*speed*dt;
        pos.y+=dir.y*speed*dt;
    }else{
        pos.x+=dir.x*speed*dt;
        pos.y+=dir.y*speed*dt;
    }
}
void player::heal(int amount){
    health += amount;
    if(health > 100)
        health = 100;
}
void player::takeDamage(int dmg){
    health -= dmg;
    if(health <= 0){
        health = 0;
        alive = false;
    }
}
void player::reset(){
    health = 240;
    alive = true;
    pos = {
        config::screen_w/2.0f,
        config::screen_h/2.0f
    };
}
void player::draw(Vector2 mouse_pos){
    float rotation=atan2(mouse_pos.y-(pos.y+assets.player.height/2),mouse_pos.x-(pos.x+assets.player.width/2))*RAD2DEG;
    Rectangle src={0,0,(float)assets.gun.width,(float)assets.gun.height};
    Rectangle dest={pos.x+18*scale,pos.y+18*scale,assets.gun.width*scale,assets.gun.height*scale};
    DrawTextureEx(assets.player,pos,0,scale,WHITE);
    DrawTexturePro(assets.gun,src,dest,{0,6*scale},rotation,WHITE);
}
