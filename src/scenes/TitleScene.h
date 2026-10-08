#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "scenes/scene.h"
#include <raylib.h>

class TitleScene : public Scene {
public:
    TitleScene ();
    ~TitleScene ();
    
    void Update() override;
    void Draw() override;

private: 
    void DrawButton (Rectangle rect, const char * text, bool hovered) ;

    Font m_font;
    Rectangle m_newGameButton;
    Rectangle m_continueButton;
    Rectangle m_exitButton;
};

#endif