#pragma once
#include <raylib.h>

namespace asset{
    constexpr const  char* player="player.png";
    constexpr const char* gun="gun.png";
    constexpr const char* bullet = "bullet.png";
    constexpr const char* map="map.png";
}
class asset_manager{
public:
Texture2D player;
Texture2D gun;
Texture2D bullet;
Texture2D map;
void load();
void unload();
};
extern asset_manager assets;
