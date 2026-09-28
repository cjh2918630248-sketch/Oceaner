#include <memory>
#include "core/Game.h"
#include "scenes/TitleScene.h"

int main(int, char**){
    Game game;
    game.SetStartingScene(std::make_unique<TitleScene>());
    game.Run();
    return 0;
}