#include "asset_loader.hpp"

void asset_manager::load(){
    player=LoadTexture(asset::player);
    player=LoadTexture(asset::gun);
    map=LoadTexture(asset::map);
}

void asset_manager::unload(){
    UnloadTexture(asset::player);
    UnloadTexture(asset::gun);
    UnloadTexture(asset::map);
}
