#include "asset_loader.hpp"

void asset_manager::load(){
    player=LoadTexture(asset::player);
    gun=LoadTexture(asset::gun);
    map=LoadTexture(asset::map);
    bullet = LoadTexture(asset::bullet);
}

void asset_manager::unload(){
    UnloadTexture(player);
    UnloadTexture(gun);
    UnloadTexture(map);
    UnloadTexture(bullet);
}

asset_manager assets;
