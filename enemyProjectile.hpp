#pragma once
#include <raylib.h>

class EnemyProjectile{
public:
bool active=true;
Vector2 pos;
Vector2 dir;
Vector2 velocity;
float speed=6.0f;
static Texture2D EnemyProjectile_texture;

EnemyProjectile(Vector2 startpos, Vector2 finalpos);
static void load();
static void unload();
void update();
void draw();
};