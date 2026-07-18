#include "ui.hpp"


void UI::menu_draw(Vector2 mouse,RenderTexture2D screen,Rectangle source,Rectangle dest){
    BeginTextureMode(screen);
    ClearBackground(BLACK);
    DrawText("Shadow Dungeon",400,150,60,RED);
    DrawRectangleRec(playButton,DARKGRAY);
    DrawRectangleRec(scoreButton,DARKGRAY);
    DrawRectangleRec(exitButton,DARKGRAY);
    DrawText("PLAY",590,270,30,WHITE);
    DrawText("HIGH SCORES",525,360,30,WHITE);
    DrawText("EXIT",595,450,30,WHITE);
    Color playColor=DARKGRAY;
    if(CheckCollisionPointRec(mouse,playButton)){
        playColor=GRAY;
        DrawRectangleRec(playButton,playColor);
        DrawText("PLAY",590,270,30,WHITE);
    }
    if(CheckCollisionPointRec(mouse,scoreButton)){
        playColor=GRAY;
        DrawRectangleRec(scoreButton,playColor);
        DrawText("HIGH SCORES",525,360,30,WHITE);
    }
    if(CheckCollisionPointRec(mouse,exitButton)){
        playColor=GRAY;
        DrawRectangleRec(exitButton,playColor);
        DrawText("EXIT",595,450,30,WHITE);
    }
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(screen.texture,source,dest,{0,0},0,WHITE);
    EndDrawing();
}
void UI::menu_update(Vector2 mouse){
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        PlaySound(click);
        if(CheckCollisionPointRec(mouse,playButton)){
            currentState=DIFFICULTY;
        }
        if(CheckCollisionPointRec(mouse,scoreButton)){
            currentState=HIGHSCORE;
        }
        if(CheckCollisionPointRec(mouse,exitButton)){
            CloseWindow();
        }
    }
}

void UI::difficulty_draw(RenderTexture2D screen,Rectangle source,Rectangle dest){

    BeginTextureMode(screen);
    ClearBackground(BLACK);
        DrawRectangleRec(easyButton, GREEN);
        DrawRectangleRec(mediumButton, ORANGE);
        DrawRectangleRec(hardButton, RED);
        DrawText("EASY",560,270,30,BLACK);
        DrawText("MEDIUM",540,360,30,BLACK);
        DrawText("HARD",560,450,30,BLACK);
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(screen.texture,source,dest,{0,0},0,WHITE);
    EndDrawing();
}

void UI::difficulty_update(Vector2 mouse){
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        PlaySound(click);
        if(CheckCollisionPointRec(mouse,easyButton)){
            gameDifficulty=EASY;
            currentState=GAME;
            config::enemy_damage = 30;
        }
        if(CheckCollisionPointRec(mouse,mediumButton)){
            gameDifficulty=MEDIUM;
            currentState=GAME;
            config::enemy_damage = 40;
        }
        if(CheckCollisionPointRec(mouse,hardButton)){
            gameDifficulty=HARD;
            currentState=GAME;
            config::enemy_damage = 60;
        }
    }
}
void UI::highscore_draw(RenderTexture2D screen,Rectangle source,Rectangle dest){
    BeginTextureMode(screen);
    ClearBackground(BLACK);
    DrawText("HIGH SCORES",450,120,50,GOLD);
    DrawText(TextFormat("EASY   : %d",highScoreEasy),500,240,35,GREEN);
    DrawText(TextFormat("MEDIUM : %d",highScoreMedium),500,320,35,ORANGE);
    DrawText(TextFormat("HARD   : %d",highScoreHard),500,400,35,RED);
    DrawText("Press M For Menu",450,520,30,WHITE);
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(screen.texture,source,dest,{0,0},0,WHITE);
    EndDrawing();

    if(IsKeyPressed(KEY_M)){
        currentState = MENU;
    }
}
void UI::highscore_update(bool player_status){
    if(!player_status){
        PlaySound(death);
        if(gameDifficulty==EASY){
            if(score>highScoreEasy){
                highScoreEasy=score;
            }
        }
        if(gameDifficulty==MEDIUM){
            if(score>highScoreMedium){
                highScoreMedium=score;
            }
        }
        if(gameDifficulty==HARD){
            if(score>highScoreHard){
                highScoreHard=score;
            }
        }
        currentState=GAMEOVER;
    }
}

void UI::gameover_draw(int score,RenderTexture2D screen,Rectangle source,Rectangle dest){
    BeginTextureMode(screen);
    ClearBackground(BLACK);
    DrawText("GAME OVER",config::screen_w/2-140,180,60,RED);
    DrawText(TextFormat("Final Score: %i",score),config::screen_w/2-140,280,30,WHITE);
    DrawText("P - PLAY AGAIN",config::screen_w/2-140,380,30,GREEN);
    DrawText("M - MAIN MENU",config::screen_w/2-140,430,30,YELLOW);
    DrawText( "Q - EXIT",config::screen_w/2-140, 480,30,RED);
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(screen.texture,source,dest,{0,0},0,WHITE);
    EndDrawing();
}
void UI::gameover_update(int score){
    if(IsKeyPressed(KEY_P)){
        reset=true;
        currentState=GAME;
    }
    if(IsKeyPressed(KEY_M)){
        reset=true;
        currentState=MENU;
    }
    if(IsKeyPressed(KEY_Q)){
        CloseWindow();
    }
}
void UI::load(){
    click=LoadSound("click.mp3");
    death=LoadSound("death.mp3");
}
void UI::unload(){
    UnloadSound(click);
    UnloadSound(death);
}


