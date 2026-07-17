#include "enemyProjectile.hpp"
#include <cmath>

EnemyProjectile::EnemyProjectile(Vector2 intPos,Vector2 targetPos){
    pos=intPos;
    dir={targetPos.x-intPos.x, targetPos.y-intPos.y};
    float len=sqrt(dir.x*dir.x+dir.y*dir.y);
    dir={dir.x/len,dir.y/len};
    velocity={dir.x*speed, dir.y*speed};
}

void EnemyProjectile::load(){
    EnemyProjectile_texture=LoadTexture("enemy_projectile.png");
}
void EnemyProjectile::unload(){
    UnloadTexture(EnemyProjectile_texture);
}
void EnemyProjectile::update(){
    pos={pos.x+=velocity.x,pos.y+=velocity.y};
}
void EnemyProjectile::draw(){
    float rotation=atan2(velocity.y,velocity.x)*RAD2DEG;
    DrawTextureEx(EnemyProjectile_texture,{pos.x-EnemyProjectile_texture.width/2,pos.y-EnemyProjectile_texture.height/2},rotation,1,WHITE);
}

