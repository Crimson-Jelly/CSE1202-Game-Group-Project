#include <iostream>
#include <cmath>
#include <raylib.h>
#include <vector>
#include "raymath.h"
using namespace std;

const int screen_w=1280;
const int screen_h=800;

class Bullet{
public:
    Vector2 pos;
    Vector2 velocity;
    float speed = 12.0f;
    bool active = true;

    static Texture2D texture;

    Bullet(Vector2 startPos, Vector2 targetPos){
        pos = startPos;

        Vector2 dir = {
            targetPos.x - startPos.x,
            targetPos.y - startPos.y
        };

        float len = sqrt(dir.x*dir.x + dir.y*dir.y);

        dir.x /= len;
        dir.y /= len;

        velocity = {
            dir.x * speed,
            dir.y * speed
        };
    }

    static void LoadAssets(){
        texture = LoadTexture("bullet.png");
    }

    static void UnloadAssets(){
        UnloadTexture(texture);
    }

    void update(){
        pos.x += velocity.x;
        pos.y += velocity.y;
    }

    void draw(){
    float rotation = atan2(velocity.y, velocity.x) * RAD2DEG;
     DrawTextureEx(
         texture, { pos.x - texture.width/2.0f, pos.y - texture.height/2.0f },
          rotation, 1.0f, WHITE 
        );
}
};

Texture2D Bullet::texture;

class EnemyBullet{
public:
    Vector2 pos;
    Vector2 velocity;
    float speed = 7.0f;

    static Texture2D texture;

    EnemyBullet(Vector2 startPos, Vector2 targetPos){

        pos = startPos;

        Vector2 dir = {
            targetPos.x - startPos.x,
            targetPos.y - startPos.y
        };

        float len = sqrt(dir.x*dir.x + dir.y*dir.y);

        dir.x /= len;
        dir.y /= len;

        velocity = {
            dir.x * speed,
            dir.y * speed
        };
    }

    static void LoadAssets(){
        texture = LoadTexture("bullet.png");
    }

    static void UnloadAssets(){
        UnloadTexture(texture);
    }

    void update(){
        pos.x += velocity.x;
        pos.y += velocity.y;
    }

    void draw(){

        float rotation =
            atan2(velocity.y, velocity.x) * RAD2DEG;

        DrawTextureEx(
            texture,
            {
                pos.x - texture.width/2.0f,
                pos.y - texture.height/2.0f
            },
            rotation,
            1.0f,
            WHITE
        );
    }
};

Texture2D EnemyBullet::texture;

class Enemy{
public:

static Texture2D texture;
    Vector2 pos;
    float speed = 1.0f;

    float shootTimer = 0.0f;

    static void LoadAssets(){
    texture = LoadTexture("zombie.png");
}

static void UnloadAssets(){
    UnloadTexture(texture);
}

    Enemy(float mapWidth,float mapHeight){

        int side = GetRandomValue(0,3);

        switch(side){

            case 0:
                pos = {
                    (float)GetRandomValue(0,mapWidth),
                    0
                };
                break;

            case 1:
                pos = {
                    (float)GetRandomValue(0,mapWidth),
                    mapHeight
                };
                break;

            case 2:
                pos = {
                    0,
                    (float)GetRandomValue(0,mapHeight)
                };
                break;

            case 3:
                pos = {
                    mapWidth,
                    (float)GetRandomValue(0,mapHeight)
                };
                break;
        }
    }

    void update(Vector2 playerPos){

        Vector2 dir = {
            playerPos.x - pos.x,
            playerPos.y - pos.y
        };

        float len = sqrt(dir.x*dir.x + dir.y*dir.y);

        if(len > 0){
            dir.x /= len;
            dir.y /= len;
        }

        pos.x += dir.x * speed;
        pos.y += dir.y * speed;
    }

   void draw(Vector2 playerPos){

    float rotation = atan2(
        playerPos.y - pos.y,
        playerPos.x - pos.x
    ) * RAD2DEG;

   float scale = 0.35f;

DrawTextureEx(
    texture,
    {
        pos.x - texture.width*scale/2,
        pos.y - texture.height*scale/2
    },
    rotation,
    scale,
    WHITE
);
}
};
 Texture2D Enemy::texture;

class map{
    public:
    Texture2D floor;
    Texture2D wall;
    RenderTexture2D screen;
    void load(){
    ChangeDirectory(TextFormat("%s/assets",GetApplicationDirectory()));
     floor=LoadTexture("Floor.png");
     wall=LoadTexture("Walls.png");
     screen=LoadRenderTexture(screen_w,screen_h);
    SetTextureFilter(screen.texture,TEXTURE_FILTER_TRILINEAR);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    }

    void draw(){
        DrawTexture(floor,0,0,WHITE);
        DrawTexture(wall,0,0,WHITE);
    }

    void unload(){
    UnloadTexture(floor);
    UnloadRenderTexture(screen);
    UnloadTexture(wall);
    }
};

class player{
    public:
    Vector2 pos;
    int health;

    Texture2D player;

    void keyboard_movement(float w,float h){
        if((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && pos.y>65){pos.y-=5;}
        if((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) && pos.y<h-115){pos.y+=5;}
        if((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && pos.x>65){pos.x-=5;}
        if((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && pos.x<w-96){pos.x+=5;}
    }

    void load(){
    player=LoadTexture("player_gun.png");
    }
    void draw(Camera2D c){
        Vector2 mouse=GetScreenToWorld2D(GetMousePosition(), c);
        float rotation=atan2(mouse.y-(pos.y+player.height/2),
        mouse.x-(pos.x+player.width/2))*RAD2DEG;
        DrawTextureEx(player,pos,rotation-8,2,WHITE);
    }
    void unload(){
        UnloadTexture(player);
    }
};

class camera{
    public:
    Camera2D camera={};
    void init(Vector2 p_pos){
        camera.offset={screen_w/2,screen_h/2};
        camera.target=p_pos;
        camera.rotation=0;
        camera.zoom=1.0f;
    }
    void movement(Vector2 p,float w,float h){
        camera.target=p;
        
        if(camera.target.x<=screen_w/2){
            camera.target.x=screen_w/2;
        }
        if(camera.target.x>=w-screen_w/2){
            camera.target.x=w-screen_w/2;
        }
        if(camera.target.y<=screen_h/2){
            camera.target.y=screen_h/2;
        }
        if(camera.target.y>=h-screen_h/2){
            camera.target.y=h-screen_h/2;
        }
    }

};

vector<Bullet> bullets;
vector<EnemyBullet> enemyBullets;
vector<Enemy> enemies;

int main(){
    float enemySpawnTimer = 0.0f;
    InitWindow(screen_w,screen_h,"GAME");
    SetTargetFPS(60);
    player player;
    camera camera;
    map map;

    player.pos={screen_w/2,screen_h/2};
    camera.init(player.pos);   
    map.load();
    player.load();
    Bullet::LoadAssets();
EnemyBullet::LoadAssets();
Enemy::LoadAssets();

    while(!WindowShouldClose()){
        player.keyboard_movement(map.floor.width,map.floor.height);
        camera.movement(player.pos,map.floor.width,map.floor.height);

if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
{
    Vector2 mouseWorld =
        GetScreenToWorld2D(
            GetMousePosition(),
            camera.camera
        );

    bullets.push_back(
        Bullet(
            player.pos,
            mouseWorld
        )
    );
}

        enemySpawnTimer += GetFrameTime();

if(enemySpawnTimer >= 3.0f){

    enemies.push_back(
        Enemy(map.floor.width,map.floor.height)
    );

    enemySpawnTimer = 0;
}
for(auto &b : bullets){
    b.update();
}
for(auto &e : enemies){

    e.update(player.pos);

    e.shootTimer += GetFrameTime();

    if(e.shootTimer >= 4.0f){

        enemyBullets.push_back(
            EnemyBullet(
                e.pos,
                player.pos
            )
        );

        e.shootTimer = 0;
    }
}
for(auto &eb : enemyBullets){
    eb.update();
}
       BeginTextureMode(map.screen);

    ClearBackground(BLACK);

    BeginMode2D(camera.camera);
        map.draw();
        for(auto &b : bullets){
            b.draw();
        }
        for(auto &e : enemies){
            e.draw(player.pos);
        }
        for(auto &eb : enemyBullets){
            eb.draw();
        }
        player.draw(camera.camera);
    EndMode2D();

EndTextureMode();
        float scale = fmin((float)GetScreenWidth()/screen_w,(float)GetScreenHeight()/screen_h);
        float offset_x=(GetScreenWidth()-screen_w*scale)/2.0;
        float offset_y=(GetScreenHeight()-screen_h*scale)/2.0;
        Rectangle source={0,0,(float)screen_w,-(float)screen_h};
        Rectangle dest={offset_x,offset_y,screen_w*scale,screen_h*scale};

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(map.screen.texture,source,dest,{0,0},0,WHITE);
        DrawText(TextFormat("%d",map.floor.width),0,0,20,WHITE);
        DrawText(TextFormat("%f",player.pos.x),0,30,20,WHITE);
        EndDrawing();
    }
    map.unload();
      for(auto &b : bullets){
    b.draw();
}
    for(auto &e : enemies){
    e.draw(player.pos);

}
for(auto &eb : enemyBullets){
    eb.draw();
}
    player.unload();
    Bullet::UnloadAssets();
EnemyBullet::UnloadAssets();
Enemy::UnloadAssets();
CloseWindow();  
return 0; 
}
