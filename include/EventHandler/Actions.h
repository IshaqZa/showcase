#ifndef ACTIONS_CLASS_H
#define ACTIONS_CLASS_H
#include <Scene/SceneManager.h>
#include <shader/shader.h>

extern SceneManager* sceneManager;

namespace actions{
    void settingsOnClick();
    void quitOnClick();
    void playOnClick();
    void playOnHoverEnter();
    void playOnHoverLeave();
    void settingsOnHoverEnter();
    void settingsOnHoverLeave();
    void quitOnHoverEnter();
    void quitOnHoverLeave();
    void empty();
}
#endif