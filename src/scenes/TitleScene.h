#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "scenes/scene.h"

class TitleScene : public Scene {
public:
    void Update() override;
    void Draw() override;
};

#endif