#include "core/SceneManager.h"

void SceneManager::PushScene(std::unique_ptr<Scene> scene) {
    scene->SetSceneManager(this);
    m_scenes.push_back(std::move(scene));
}

void SceneManager::PopScene() {
    if (!m_scenes.empty()) {
        m_scenes.pop_back();
    }
}

void SceneManager::ChangeScene(std::unique_ptr<Scene> scene) {
    if (!m_scenes.empty()) {
        m_scenes.pop_back();
    }
    scene->SetSceneManager(this);
    m_scenes.push_back(std::move(scene));
}

void SceneManager::Update() {
    if (!m_scenes.empty()) {
        m_scenes.back()->Update();
    }
}

void SceneManager::Draw() {
    for (auto& scene : m_scenes) {
        scene->Draw();
    }
}

bool SceneManager::IsEmpty() const {
    return m_scenes.empty();
}

void SceneManager::Clear() {
    m_scenes.clear();
}

void SceneManager::RequestQuit() {
    m_shouldQuit = true;
}

bool SceneManager::ShouldQuit() const {
    return m_shouldQuit;
}