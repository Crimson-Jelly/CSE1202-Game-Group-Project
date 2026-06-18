#include <iostream>
#include <raylib.h>

int main(){
    ChangeDirectory(TextFormat("%s/assets",GetApplicationDirectory()));
    std::cout<<GetWorkingDirectory()<<'\n';
    std::cout<<GetApplicationDirectory();

    return 0;

}