#pragma once
#include "raylib.h"
#include "global.hpp"

enum GameState{
    MENU,
    DIFFICULTY,
    GAME,
    HIGHSCORE,
    EXITGAME,
    GAMEOVER
};
enum Difficulty{
    EASY,
    MEDIUM,
    HARD
};

class UI{
public:
    Difficulty gameDifficulty=EASY;
    GameState currentState=MENU;

    Rectangle playButton={490,250,300,60};
    Rectangle scoreButton={490,340,300,60};
    Rectangle exitButton={490,430,300,60};

    Rectangle easyButton={490,250,300,60};
    Rectangle mediumButton={490,340,300,60};
    Rectangle hardButton={490,430,300,60};

    int score=0;
    int highScoreEasy=0;
    int highScoreMedium=0;
    int highScoreHard=0;

    void menu_draw(Vector2 mouse,RenderTexture2D screen,Rectangle source,Rectangle dest);
    void menu_update(Vector2 mouse);
    void difficulty_draw(RenderTexture2D screen,Rectangle source,Rectangle dest);
    void difficulty_update(Vector2 mouse);
    void highscore_update(bool player_status);
    void highscore_draw(RenderTexture2D screen,Rectangle source,Rectangle dest);
    void gameover_draw(int score,RenderTexture2D screen,Rectangle source,Rectangle dest);
    void gameover_update(int score);
};