#ifndef GAMESCENE_CLASS_H
#define GAMESCENE_CLASS_H

#include <Scene/Scene.h>
#include <GameScene/GameObject.h>


class GameScene : public Scene {

    private:

        std::unordered_map<std::string, std::shared_ptr<GameObject>> elements;

    public:
        std::shared_ptr<GameObject> getElementByName(std::string name);
        void addElement(std::string name, std::shared_ptr<GameObject> element);
        void update(GLFWwindow* window) override;
        void render() override;
};

#endif