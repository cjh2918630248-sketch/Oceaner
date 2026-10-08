#ifndef SCENE_H
#define SCENE_H

class SceneManager ;
class Scene {
public:
    virtual ~Scene() = default;
    virtual void Update() = 0;
    virtual void Draw() = 0;

    void SetSceneManager (SceneManager* manager) { m_sceneManager = manager; }
    
protected:
    SceneManager* m_sceneManager = nullptr;
};

#endif