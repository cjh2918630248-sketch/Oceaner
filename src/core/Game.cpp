#include "core/Game.h"
#include <raylib.h>

Game::Game() : m_running(false) {
    InitWindow(800, 600, "Oceaner");
}

Game::~Game() {
    CloseWindow();
}

void Game::SetStartingScene(std::unique_ptr<Scene> scene) {
    m_sceneManager.PushScene(std::move(scene));
}

void Game::Run() {
    m_running = true;
    while (m_running && !WindowShouldClose()) {
        Update();
        Draw();
    }
}

void Game::Update() {
    m_sceneManager.Update();
    if (m_sceneManager.IsEmpty()) {
        m_running = false;
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    m_sceneManager.Draw();
    EndDrawing();
}