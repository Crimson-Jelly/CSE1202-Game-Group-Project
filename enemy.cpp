#include "enemy.hpp"
#include <math.h>

Enemy::Enemy(float mapWidth,float mapHeight){
    int side=GetRandomValue(0,3);
    switch(side){
        case 0:
            pos={(float)GetRandomValue(10,mapWidth),10};
            break;
        case 1:
            pos={(float)GetRandomValue(10,mapWidth),mapHeight};
            break;
        case 2:
            pos={0,(float)GetRandomValue(10,mapHeight)};
            break;
        case 3:
            pos={mapWidth,(float)GetRandomValue(10,mapHeight)};
            break;
        }
}

void Enemy::load(){
    enemy_texture=LoadTexture("enemy1.png");
}

void Enemy::unload(){
    UnloadTexture(enemy_texture);
}
void Enemy::movement(Vector2 playerPos){
    Vector2 dir={playerPos.x-pos.x,playerPos.y-pos.y};
    float len=sqrt(dir.x*dir.x + dir.y*dir.y);
    if(len>0) dir={dir.x/len,dir.y/len};
    pos={pos.x+=dir.x*speed,pos.y+=dir.y*speed};
}

void Enemy::draw(Vector2 playerPos){
    float scale=5;
    DrawTextureEx(enemy_texture,{pos.x-enemy_texture.width*scale/2,pos.y-enemy_texture.height*scale/2},0,scale,WHITE);
    DrawText(TextFormat("%i",health),pos.x,pos.y-30,20,RED);
}