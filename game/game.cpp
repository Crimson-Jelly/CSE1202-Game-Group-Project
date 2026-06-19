#include <iostream>
#include <cmath>
#include <raylib.h>

const int screen_w=1280;
const int screen_h=800;
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
        float rotation=atan2(mouse.y-(pos.y+player.height/2),mouse.x-(pos.x+player.width/2))*RAD2DEG;
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

int main(){
    InitWindow(screen_w,screen_h,"GAME");
    SetTargetFPS(60);
    player player;
    camera camera;
    map map;

    player.pos={screen_w/2,screen_h/2};
    camera.init(player.pos);   
    map.load();
    player.load();

    while(!WindowShouldClose()){
        player.keyboard_movement(map.floor.width,map.floor.height);
        camera.movement(player.pos,map.floor.width,map.floor.height);

        BeginTextureMode(map.screen);
            ClearBackground(BLACK);
            BeginMode2D(camera.camera);
            map.draw();
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
    player.unload();
CloseWindow();  
return 0; 
}
