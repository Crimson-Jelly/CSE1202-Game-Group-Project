#pragma once
#include <raylib.h>

class map{
    public:
    Texture2D map;
    RenderTexture2D screen;
    void draw();
    void load();
    void unload();

};
