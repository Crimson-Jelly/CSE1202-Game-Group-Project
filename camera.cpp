#include "camera.hpp"
#include "global.hpp"

void camera::init(Vector2 p_pos){
    camera.offset={config::screen_w/2,config::screen_h/2};
    camera.target=p_pos;
    camera.rotation=0;
    camera.zoom=1.0f;
}

void camera::movement(Vector2 p_pos,float w,float h){
    camera.target=p_pos;
        
    if(camera.target.x<=config::screen_w/2){
        camera.target.x=config::screen_w/2;
    }
    if(camera.target.x>=w-config::screen_w/2){
        camera.target.x=w-config::screen_w/2;
    }
    if(camera.target.y<=config::screen_h/2){
        camera.target.y=config::screen_h/2;
    }
    if(camera.target.y>=h-config::screen_h/2){
        camera.target.y=h-config::screen_h/2;
    }
}