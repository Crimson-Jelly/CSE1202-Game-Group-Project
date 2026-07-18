#include "bullet.hpp"
#include "global.hpp"


Bullet::Bullet(Vector2 intpos,Vector2 targetpos){
    pos={intpos.x+18*config::scale,intpos.y+16*config::scale};
    dir={targetpos.x-pos.x, targetpos.y-pos.y};
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
    DrawTextureEx(bullet_texture,pos,rotation,0.5,WHITE);
}
void Bullet::load(){
    bullet_texture=LoadTexture("bullet.png");
}
void Bullet::unload(){
    UnloadTexture(bullet_texture);
}


