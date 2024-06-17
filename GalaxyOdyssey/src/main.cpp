#include "GameManager.h"

int main(int  argc, char * argv[]){
    GameManager * Game = GameManager::Instance();
    Game->Instance()->Run();

    GameManager::Release();
    Game = nullptr;

    return 0;
}