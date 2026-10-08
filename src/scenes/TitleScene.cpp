#include "scenes/TitleScene.h"
#include "core/SceneManager.h"
#include "scenes/BattleScene.h"
#include <stdio.h>
#include <memory>

TitleScene::TitleScene() {
    int codepoints[] = {
        0x65B0, 0x7684, 0x6E38, 0x620F,
        0x7EE7, 0x7EED, 0x9000, 0x51FA
    };
    m_font = LoadFontEx("assets/font/TerrarumSansBitmap.otf", 28, codepoints, 8);
    if (m_font.glyphCount == 0) {
        printf("警告：字体加载失败，请确认 assets/font/TerrarumSansBitmap.otf 存在\n");
        m_font = GetFontDefault();
    }

    float btnWidth = 220.0f;
    float btnHeight = 55.0f;
    float x = 800.0f / 2 - btnWidth / 2;
    m_newGameButton = { x, 260, btnWidth, btnHeight };
    m_continueButton = { x, 330, btnWidth, btnHeight };
    m_exitButton = { x, 400, btnWidth, btnHeight };
}

TitleScene::~TitleScene() {
    UnloadFont(m_font);
}

void TitleScene::Update() {
    Vector2 mouse = GetMousePosition();

    if (CheckCollisionPointRec(mouse, m_continueButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        m_sceneManager->ChangeScene(std::make_unique<BattleScene>());
    }

    if (CheckCollisionPointRec(mouse, m_exitButton) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        m_sceneManager->RequestQuit();
    }
}

void TitleScene::Draw() {
    int titleWidth = MeasureText("Oceaner", 60);
    DrawText("Oceaner", 800 / 2 - titleWidth / 2, 140, 60, DARKGRAY);

    Vector2 mouse = GetMousePosition();
    DrawButton(m_newGameButton, "新的游戏", CheckCollisionPointRec(mouse, m_newGameButton));
    DrawButton(m_continueButton, "继续游戏", CheckCollisionPointRec(mouse, m_continueButton));
    DrawButton(m_exitButton, "退出游戏", CheckCollisionPointRec(mouse, m_exitButton));
}

void TitleScene::DrawButton(Rectangle rect, const char* text, bool hovered) {
    Color bg = hovered ? SKYBLUE : LIGHTGRAY;
    DrawRectangleRec(rect, bg);
    DrawRectangleLinesEx(rect, 2, DARKGRAY);

    float fontSize = 28;
    Vector2 textSize = MeasureTextEx(m_font, text, fontSize, 1);
    Vector2 pos = {
        rect.x + (rect.width - textSize.x) / 2,
        rect.y + (rect.height - textSize.y) / 2
    };
    DrawTextEx(m_font, text, pos, fontSize, 1, BLACK);
}