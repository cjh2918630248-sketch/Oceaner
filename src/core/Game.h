#ifndef GAME_H
#define GAME_H

#include <memory>
#include "core/SceneManager.h"
#include "scenes/scene.h"

class Game {
public:
    Game();
    ~Game();

    void Run();
    void SetStartingScene(std::unique_ptr<Scene> scene);

private:
    void Update();
    void Draw();

    SceneManager m_sceneManager;
    bool m_running;
};

#endif