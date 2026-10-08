#include <cstdlib>
#include <memory>
#include "core/Game.h"
#include "scenes/TitleScene.h"

int main(int, char**){
    system("chcp 65001 > nul");
    Game game;
    game.SetStartingScene(std::make_unique<TitleScene>());
    game.Run();
    return 0;
}