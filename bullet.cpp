#include "asset_loader.hpp"
#include "bullet.hpp"
#include "player.hpp"

Bullet::Bullet(Vector2 intpos,Vector2 targetpos){
    dir={targetpos.x-intpos.x, targetpos.y-intpos.y};
    float len=sqrt(dir.x*dir.x+dir.y*dir.y);
    dir={dir.x/len,dir.y/len};
    velocity={dir.x*speed, dir.y*speed};
}
void Bullet::update(){
    pos.x += velocity.x;
    pos.y += velocity.y;
}

void Bullet::draw(Vector2 mouse_pos){
    float rotation=atan2(velocity.y,velocity.x)*RAD2DEG;
    DrawTextureEx(assets.bullet,pos,0,1,WHITE);
}


