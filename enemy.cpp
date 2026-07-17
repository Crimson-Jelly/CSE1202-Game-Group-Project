#include "enemy.hpp"
#include <math.h>

Enemy::Enemy(float mapWidth,float mapHeight){
    int side=GetRandomValue(0,3);
    switch(side){
        case 0:
            pos={(float)GetRandomValue(0,mapWidth),0};
            break;
        case 1:
            pos={(float)GetRandomValue(0,mapWidth),mapHeight};
            break;
        case 2:
            pos={0,(float)GetRandomValue(0,mapHeight)};
            break;
        case 3:
            pos={mapWidth,(float)GetRandomValue(0,mapHeight)};
            break;
        }
}

void Enemy::load(){
    enemy_texture=LoadTexture("enemy.png");
}

void Enemy::unload(){
    UnloadTexture(enemy_texture);
}
void Enemy::update(Vector2 playerPos){
    Vector2 dir={playerPos.x-pos.x,playerPos.y-pos.y};
    float len=sqrt(dir.x*dir.x + dir.y*dir.y);
    if(len>0){
    dir.x /= len;
    dir.y /= len;
    }

    pos.x+= dir.x*speed;
    pos.y+= dir.y*speed;
}

void Enemy::draw(Vector2 playerPos){
    float rotation=atan2(playerPos.y-pos.y,playerPos.x-pos.x)*RAD2DEG;
    float scale=5;

DrawTextureEx(enemy_texture,{pos.x-enemy_texture.width*scale/2,pos.y-enemy_texture.height*scale/2},rotation,scale,WHITE);
DrawText(TextFormat("%i",health),pos.x,pos.y-30,20,RED);
}