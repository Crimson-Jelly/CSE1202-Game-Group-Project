#include <iostream>
#include <cmath>
#include <raylib.h>
#include <vector>
#include <raymath.h>
#include <algorithm>

#include "player.hpp"
#include "map.hpp"
#include "camera.hpp"
#include "bullet.hpp"
#include "global.hpp"
#include "enemy.hpp"
#include "enemyProjectile.hpp"
#include "med.hpp"
#include "ui.hpp"

Texture2D Bullet::bullet_texture;
Texture2D Enemy::enemy_texture;
Texture2D EnemyProjectile::EnemyProjectile_texture;

int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(config::screen_w,config::screen_h,"Shadow Dungeon");
    SetTargetFPS(60);
    //create instances of classes
    player player;
    camera camera;
    map map;
    Medkit med;
    UI ui;
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    std::vector<EnemyProjectile> projectiles;
    //some initialization
    player.pos={config::screen_w/2,config::screen_h/2};
    camera.init(player.pos);
    float enemy_spawntimer=0.0f;
    
    //load asset
    map.load();
    player.load();
    med.load();
    Bullet::load();
    Enemy::load();
    EnemyProjectile::load();
    InitAudioDevice();
    ui.load();
    Music bgm=LoadMusicStream("mars.wav");
    Music menu=LoadMusicStream("menu.mp3");
    PlayMusicStream(bgm);
    PlayMusicStream(menu);

    while(!WindowShouldClose()){
        //setting up resizable window
        float scale = fmin((float)GetScreenWidth()/config::screen_w,(float)GetScreenHeight()/config::screen_h);
        float offset_x=(GetScreenWidth()-config::screen_w*scale)/2.0;
        float offset_y=(GetScreenHeight()-config::screen_h*scale)/2.0;
        Rectangle source={0,0,(float)config::screen_w,-(float)config::screen_h};
        Rectangle dest={offset_x,offset_y,config::screen_w*scale,config::screen_h*scale};
        //setting up mouse
        Vector2 mouse=GetMousePosition();
        mouse.x=(mouse.x-dest.x)/scale;
        mouse.y=(mouse.y-dest.y)/scale;
        Vector2 mouse_pos=GetScreenToWorld2D(mouse, camera.camera);
        //checking different game state
        if(ui.currentState==MENU){
            ui.menu_draw(mouse,map.screen,source,dest);
            ui.menu_update(mouse);
        }
        if(ui.currentState==DIFFICULTY){
            ui.difficulty_draw(map.screen,source,dest);
            ui.difficulty_update(mouse);
        }
        if(ui.currentState==HIGHSCORE){
            ui.highscore_draw(map.screen,source,dest);
        }
        if(ui.currentState==HIGHSCORE || ui.currentState==DIFFICULTY || ui.currentState==MENU){
            UpdateMusicStream(menu);
        }
        if(ui.currentState==GAME){
        player.keyboard_movement(map.map.width*config::size,map.map.height*config::size);
        camera.movement(player.pos,map.map.width*config::size,map.map.height*config::size);
        med.init(map.map.width*config::size, map.map.height*config::size);
        med.despawn(player.pos,player.health);

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            bullets.push_back(Bullet(player.pos,mouse_pos));
        }
        //spawn enemy
        enemy_spawntimer+=GetFrameTime();
        if(enemy_spawntimer>=3){
        enemies.push_back(Enemy(map.map.width*config::size,map.map.height*config::size));
        enemy_spawntimer=0;
        }
        //enemy shoot logic
        for(auto& enemy:enemies){
            enemy.movement(player.pos);
            enemy.shoot_timer+=GetFrameTime();
            if(enemy.shoot_timer>=enemy.atk_speed){
            projectiles.push_back(EnemyProjectile(enemy.pos, player.pos));
            enemy.shoot_timer=0;
            }
        }
        for(auto& projectile:projectiles){
            projectile.update();
            if(!projectile.active) continue;
            if(!player.alive) continue;
                float dist=Vector2Distance(projectile.pos,player.pos);
                if(dist<player.hitbox){
                    player.health-=config::enemy_damage;
                    projectile.active=false;
                    if(player.health<=0){
                        player.alive=false;
                    }
                }
        }
        //player shoot logic
        if(player.alive){
            for(auto& bullet:bullets){
                bullet.update();
                if(!bullet.active) continue;
                for(auto& enemy:enemies){
                    if(!enemy.alive) continue;
                    float dist=Vector2Distance(bullet.pos,enemy.pos);
                    if(dist<enemy.hitbox){
                        enemy.health-=bullet.damage;
                        bullet.active=false;
                        if(enemy.health<=0){
                            enemy.alive=false;
                            ui.score+=10;
                        }
                    }
                }
            }
        }
        ui.highscore_update(player.alive);
        //removing garbage
        enemies.erase(remove_if(enemies.begin(),enemies.end(),[](Enemy &enemy){return !enemy.alive;}),enemies.end());
        projectiles.erase(remove_if(projectiles.begin(),projectiles.end(),[](EnemyProjectile &projectile){return !projectile.active;}),projectiles.end());
        bullets.erase(remove_if(bullets.begin(),bullets.end(),[](Bullet &bullet){return !bullet.active;}),bullets.end());
        //draw
        UpdateMusicStream(bgm);
        BeginTextureMode(map.screen);
            ClearBackground(BLACK);
            BeginMode2D(camera.camera);
            map.draw();
            player.draw(mouse_pos);
            med.draw();

            if(player.alive){
                for(auto& bullet:bullets){
                    bullet.draw(mouse_pos);
                }
            }
            for(auto& enemy:enemies){
                enemy.draw(player.pos);
            }
            for(auto& projectile:projectiles) projectile.draw();
            EndMode2D();
        EndTextureMode();
    
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(map.screen.texture,source,dest,{0,0},0,WHITE);
        DrawText(TextFormat("HP: %i",player.health),20,20,30,GREEN);
        DrawText(TextFormat("SCORE: %i",ui.score),20,50,30,YELLOW);
        EndDrawing();
    }
    if(ui.currentState==GAMEOVER){
        ui.gameover_draw(ui.score,map.screen,source,dest);
        ui.gameover_update(ui.score);
    }
    if(ui.reset){
        player.reset();
        bullets.clear();
        enemies.clear();
        projectiles.clear();
        med.active=false;
        med.timer=0;
        enemy_spawntimer=0;
        ui.score=0;
        ui.reset=false;
    }
}
    map.unload();
    player.unload();
    med.unload();
    ui.unload();
    Bullet::unload();
    Enemy::unload();
    EnemyProjectile::unload();
    UnloadMusicStream(bgm);
    UnloadMusicStream(menu);
    
CloseAudioDevice();
CloseWindow();
  
return 0;
}