#include "GameManager.h"

int main(int  argc, char * argv[]){
    GameManager * Game = GameManager::Instance();
    Game->Run();

    GameManager::Release();
    Game = NULL;
}