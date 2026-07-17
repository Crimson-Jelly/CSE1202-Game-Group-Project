#include <iostream>
#include <cmath>
#include <raylib.h>
#include <vector>

#include "player.hpp"
#include "map.hpp"
#include "camera.hpp"
#include "bullet.hpp"
#include "global.hpp"
enum GameState{
    MENU,
    DIFFICULTY,
    GAME,
    HIGHSCORE,
    EXITGAME
};
enum Difficulty{
    EASY,
    MEDIUM,
    HARD
};
Difficulty gameDifficulty = EASY;

GameState currentState = MENU;

Texture2D Bullet::bullet;

int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(config::screen_w,config::screen_h,"GAME");
    SetTargetFPS(60);
    player player;
    camera camera;
    map map;
    std::vector<Bullet> bullets;

    player.pos={config::screen_w/2,config::screen_h/2};
    camera.init(player.pos);

    map.load();
    player.load();
    bullet.load();

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
        SetDifficulty(EASY);
        currentState = GAME;
    }
    if(CheckCollisionPointRec(mouse, mediumButton)){
        SetDifficulty(MEDIUM);
        currentState = GAME;
    }
    if(CheckCollisionPointRec(mouse, hardButton)){
        SetDifficulty(HARD);
        currentState = GAME;
    }
}
            if(currentState == GAME){
        player.keyboard_movement(map.map.width*config::size,map.map.height*config::size);
        camera.movement(player.pos,map.map.width*config::size,map.map.height*config::size);
        Vector2 mouse_pos=GetScreenToWorld2D(GetMousePosition(), camera.camera);

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            bullets.push_back(Bullet(player.pos,mouse_pos));
        }

        UpdateMusicStream(bgm);
        BeginTextureMode(map.screen);
            ClearBackground(BLACK);
            BeginMode2D(camera.camera);
            map.draw();
            player.draw(mouse_pos);
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
        }
    map.unload();
    player.unload();
    Bullet::unload();
    UnloadMusicStream(bgm);
CloseAudioDevice();
CloseWindow();  
return 0; 
}
