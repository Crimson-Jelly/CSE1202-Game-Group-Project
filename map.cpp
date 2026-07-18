#include "map.hpp"
#include "global.hpp"

void map::load(){
    ChangeDirectory(TextFormat("%s/assets",GetApplicationDirectory()));
    map=LoadTexture("map.png");
    screen=LoadRenderTexture(config::screen_w,config::screen_h);
    SetTextureFilter(screen.texture,TEXTURE_FILTER_TRILINEAR);
}

void map::draw(){
    DrawTextureEx(map,{0,0},0,config::size,WHITE);
}

void map::unload(){
    UnloadTexture(map);
    UnloadRenderTexture(screen);
}
