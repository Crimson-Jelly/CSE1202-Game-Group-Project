#include <iostream>
#include <cmath>
#include <raylib.h>
#include <vector>

#include "player.hpp"
#include "map.hpp"
#include "camera.hpp"
#include "bullet.hpp"
#include "global.hpp"
#include "enemy.hpp"

Texture2D Bullet::bullet_texture;
Texture2D Enemy::enemy_texture;


int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(config::screen_w,config::screen_h,"GAME");
    SetTargetFPS(60);
    player player;
    camera camera;
    map map;
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;

    player.pos={config::screen_w/2,config::screen_h/2};
    camera.init(player.pos);
    float enemy_spawntimer=0.0f;

    map.load();
    player.load();
    Bullet::load();
    Enemy::load();
    InitAudioDevice();
    Music bgm=LoadMusicStream("bgm2.wav");
    //PlayMusicStream(bgm);


    while(!WindowShouldClose()){
        player.keyboard_movement(map.map.width*config::size,map.map.height*config::size);
        camera.movement(player.pos,map.map.width*config::size,map.map.height*config::size);
        Vector2 mouse_pos=GetScreenToWorld2D(GetMousePosition(), camera.camera);

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            bullets.push_back(Bullet(player.pos,mouse_pos));
        }

        enemy_spawntimer+=GetFrameTime();
        if(enemy_spawntimer>=3.0f){
        enemies.push_back(Enemy(map.map.width*config::size,map.map.height*config::size));
        enemy_spawntimer=0;
        }
        UpdateMusicStream(bgm);
        BeginTextureMode(map.screen);
            ClearBackground(BLACK);
            BeginMode2D(camera.camera);
            map.draw();
            player.draw(mouse_pos);
        for(auto& bullet:bullets)
        {
        bullet.update();
        bullet.draw(mouse_pos);
        }
        for(auto& enemy:enemies){
        enemy.draw(player.pos);
        }
            EndMode2D();
        EndTextureMode();

        float scale = fmin((float)GetScreenWidth()/config::screen_w,(float)GetScreenHeight()/config::screen_h);
        float offset_x=(GetScreenWidth()-config::screen_w*scale)/2.0;
        float offset_y=(GetScreenHeight()-config::screen_h*scale)/2.0;
        Rectangle source={0,0,(float)config::screen_w,-(float)config::screen_h};
        Rectangle dest={offset_x,offset_y,config::screen_w*scale,config::screen_h*scale};

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(map.screen.texture,source,dest,{0,0},0,WHITE);
        EndDrawing();
    }
    map.unload();
    player.unload();
    Bullet::unload();
    Enemy::unload();
    UnloadMusicStream(bgm);
CloseAudioDevice();
CloseWindow();  
return 0; 
}