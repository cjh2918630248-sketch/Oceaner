#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <memory>
#include <vector>
#include "scenes/scene.h"

class SceneManager {
public:
    void PushScene(std::unique_ptr<Scene> scene);
    void PopScene();
    void ChangeScene(std::unique_ptr<Scene> scene);
    void Update();
    void Draw();
    bool IsEmpty() const;
    void Clear();

    void RequestQuit(); 
    bool ShouldQuit() const;

private:
    std::vector<std::unique_ptr<Scene>> m_scenes;
    bool m_shouldQuit = false;
};

#endif