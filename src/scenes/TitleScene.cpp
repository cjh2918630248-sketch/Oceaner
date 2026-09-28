#include "scenes/TitleScene.h"
#include <raylib.h>

void TitleScene::Update() {
}

void TitleScene::Draw() {
    DrawText("Oceaner", 320, 250, 40, DARKGRAY);
    DrawText("Press ENTER to start", 290, 320, 20, LIGHTGRAY);
}