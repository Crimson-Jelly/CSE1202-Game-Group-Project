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
#include "asset_loader.hpp"
#include "global.hpp"
#include "enemy.hpp"
#include "enemyProjectile.hpp"
#include "med.hpp"
enum GameState{
    MENU,
    DIFFICULTY,
    GAME,
    GAMEOVER,
    HIGHSCORE,
    EXITGAME
};
enum Difficulty{
    EASY,
    MEDIUM,
    HARD
};
Texture2D Enemy::enemy_texture;
Texture2D EnemyProjectile::EnemyProjectile_texture;
Texture2D Bullet::bullet_texture;

Difficulty gameDifficulty = EASY;

GameState currentState = MENU;

void ResetGame(player& player,std::vector<Bullet>& bullets,std::vector<Enemy>& enemies,
    std::vector<EnemyProjectile>& projectiles, Medikit& med, float& enemy_spawntimer){
    player.reset();
    bullets.clear();
    enemies.clear();
    projectiles.clear();
    med.active = false;
    med.timer = 0.0f;
    enemy_spawntimer = 0.0f;
}

int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(config::screen_w,config::screen_h,"GAME");
    SetTargetFPS(60);
    player player;
    camera camera;
    map map;
    std::vector<Bullet> bullets;
      std::vector<Enemy> enemies;
    std::vector<EnemyProjectile> projectiles;
    Medikit med;
    int score = 0;
    int highScoreEasy = 0;
    int highScoreMedium = 0;
    int highScoreHard = 0;

    player.pos={config::screen_w/2,config::screen_h/2};
    camera.init(player.pos);
     float enemy_spawntimer=0.0f;
     map.load();
assets.load();
med.load();
Bullet::load();
Enemy::load();
EnemyProjectile::load();

    InitAudioDevice();
    Music bgm=LoadMusicStream("bgm2.wav");
    //PlayMusicStream(bgm);

    while(!WindowShouldClose()){
        if(currentState == MENU){
Rectangle playButton = {490, 250, 300, 60};
Rectangle scoreButton = {490, 340, 300, 60};
Rectangle exitButton = {490, 430, 300, 60};
BeginDrawing();
ClearBackground(BLACK);
DrawRectangleRec(playButton, DARKGRAY);
DrawRectangleRec(scoreButton, DARKGRAY);
DrawRectangleRec(exitButton, DARKGRAY);
DrawText("PLAY", 590, 270, 30, WHITE);
DrawText("HIGH SCORES", 525, 360, 30, WHITE);
DrawText("EXIT", 595, 450, 30, WHITE);
            Vector2 mouse = GetMousePosition();
Color playColor = DARKGRAY;
if(CheckCollisionPointRec(mouse, playButton)){
    playColor = GRAY;
DrawRectangleRec(playButton, playColor);
}
if(CheckCollisionPointRec(mouse, scoreButton)){
    playColor = GRAY;
DrawRectangleRec(scoreButton, playColor);
}
if(CheckCollisionPointRec(mouse, exitButton)){
    playColor = GRAY;
DrawRectangleRec(exitButton, playColor);
}
    EndDrawing();

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
    Vector2 mouse = GetMousePosition();
    if(CheckCollisionPointRec(mouse, playButton)){
        currentState = DIFFICULTY;
    }
    if(CheckCollisionPointRec(mouse, scoreButton)){
        currentState = HIGHSCORE;
    }
    if(CheckCollisionPointRec(mouse, exitButton)){
        CloseWindow();
    }
}
    continue;
}
if(currentState == HIGHSCORE){
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("HIGH SCORES", 450, 120, 50, GOLD);
    DrawText(TextFormat("EASY   : %d", highScoreEasy), 500, 240, 35, GREEN);
    DrawText(TextFormat("MEDIUM : %d", highScoreMedium), 500, 320, 35, ORANGE);
    DrawText(TextFormat("HARD   : %d", highScoreHard), 500, 400, 35, RED);
    DrawText("Press M For Menu", 450, 520, 30, WHITE);
    EndDrawing();
    if(IsKeyPressed(KEY_M)){
        currentState = MENU;
    }
    continue;
}
        if(currentState == DIFFICULTY){
    BeginDrawing();
    ClearBackground(BLACK);
   Rectangle easyButton   = {490,250,300,60};
Rectangle mediumButton = {490,340,300,60};
Rectangle hardButton   = {490,430,300,60};
DrawRectangleRec(easyButton, GREEN);
DrawRectangleRec(mediumButton, ORANGE);
DrawRectangleRec(hardButton, RED);
DrawText("EASY",560,270,30,BLACK);
DrawText("MEDIUM",540,360,30,BLACK);
DrawText("HARD",560,450,30,BLACK);
    EndDrawing();
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
    Vector2 mouse = GetMousePosition();
    if(CheckCollisionPointRec(mouse, easyButton)){
        gameDifficulty = EASY;
        currentState = GAME;
    }
    if(CheckCollisionPointRec(mouse, mediumButton)){
        gameDifficulty= MEDIUM;
        config::enemy_damage = 40;
        currentState = GAME;
    }
    if(CheckCollisionPointRec(mouse, hardButton)){
        gameDifficulty = HARD;
        config::enemy_damage = 60;
        currentState = GAME;
    }
}
}
            if(currentState == GAME){
        player.keyboard_movement(map.map.width*config::size,map.map.height*config::size);
        camera.movement(player.pos,map.map.width*config::size,map.map.height*config::size);
        Vector2 mouse_pos=GetScreenToWorld2D(GetMousePosition(), camera.camera);
        med.update(map.map.width*config::size, map.map.height*config::size);

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            bullets.push_back(Bullet(player.pos,mouse_pos));
        }
          enemy_spawntimer+=GetFrameTime();
        if(enemy_spawntimer>=3){
        enemies.push_back(Enemy(map.map.width*config::size,map.map.height*config::size));
        enemy_spawntimer=0;
        }
        for(auto& enemy:enemies){
            enemy.shoot_timer+=GetFrameTime();
            if(enemy.shoot_timer >= enemy.atk_speed){
            projectiles.push_back(EnemyProjectile(enemy.pos, player.pos));
            enemy.shoot_timer = 0;
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
         for(auto& bullet:bullets){
            if(!bullet.active) continue;
                for(auto& enemy:enemies){
                    if(!enemy.alive) continue;
                    float dist=Vector2Distance(bullet.pos,enemy.pos);
                    if(dist<enemy.hitbox){
                        enemy.health-=bullet.damage;
                        bullet.active=false;
                        if(enemy.health<=0){
                            enemy.alive=false;
                            score+=10;
                        }
                    }
            }
        }
if(!player.alive){
    if(gameDifficulty == EASY){
        if(score > highScoreEasy){
        highScoreEasy = score;
        }
}
    if(gameDifficulty == MEDIUM){
        if(score > highScoreMedium){
        highScoreMedium = score;
        }
}
    if(gameDifficulty == HARD){
        if(score > highScoreHard){
        highScoreHard = score;
        }
}
    currentState = GAMEOVER;
}
        enemies.erase(remove_if(enemies.begin(),enemies.end(),[](Enemy &enemy){return !enemy.alive;}),enemies.end());
        bullets.erase(
    remove_if(bullets.begin(), bullets.end(), [](Bullet &b){
        return !b.active;
    }),
    bullets.end()
);
projectiles.erase(
    remove_if(
        projectiles.begin(),
        projectiles.end(),
        [](EnemyProjectile &b)
        {
            return !b.active;
        }),
    projectiles.end()
);
if(currentState == GAMEOVER){
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("GAME OVER", config::screen_w/2 - 140, 180, 60, RED);
    DrawText(TextFormat("Final Score: %i", score), config::screen_w/2 - 140, 280, 30, WHITE);
    DrawText("P - PLAY AGAIN", config::screen_w/2 - 140, 380, 30, GREEN);
    DrawText("M - MAIN MENU", config::screen_w/2 - 140, 430, 30, YELLOW);
    DrawText( "Q - EXIT", config::screen_w/2 - 140, 480, 30, RED);
    EndDrawing();
    if(IsKeyPressed(KEY_P)){
        ResetGame(player, bullets, enemies, projectiles, med, enemy_spawntimer);
        score = 0;
        currentState = GAME;
    }
    if(IsKeyPressed(KEY_M)){
        ResetGame( player, bullets, enemies, projectiles, med, enemy_spawntimer);
        score = 0;
        currentState = MENU;
    }
    if(IsKeyPressed(KEY_Q)){
        CloseWindow();
    }
    continue;
}

        UpdateMusicStream(bgm);
        BeginTextureMode(map.screen);
            ClearBackground(BLACK);
            BeginMode2D(camera.camera);
            map.draw();
            med.draw();
            player.draw(mouse_pos);
             if(player.alive){
                for(auto& bullet:bullets){
                    bullet.update();
                    bullet.draw(mouse_pos);
                }
            }
            for(auto& enemy:enemies){
                enemy.movement(player.pos);
                enemy.draw(player.pos);
            }
            for(auto& projectile:projectiles) projectile.draw();
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
         DrawText(TextFormat("HP: %i", player.health), 20, 20, 30, GREEN);
    DrawText(TextFormat("Score: %i", score), 20, 60, 30, YELLOW);
        EndDrawing();
    }
}
map.unload();
med.unload();
assets.unload();
Enemy::unload();
Bullet::unload();
    EnemyProjectile::unload();
    UnloadMusicStream(bgm);
CloseAudioDevice();
CloseWindow();  
return 0; 
}