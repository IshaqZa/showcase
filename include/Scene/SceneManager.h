#ifndef SCENE_MANAGER_CLASS_H
#define SCENE_MANAGER_CLASS_H

#include "Scene/Scene.h"

class Scene;
class EventHandler;

class SceneManager {

    private:
        std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
        std::string currScene;
        static SceneManager* instancePtr;

        SceneManager(){}
    public:
        SceneManager(const SceneManager& obj) = delete;

        static SceneManager* getInstance();

        void addScene(std::string name, std::shared_ptr<Scene> scene);
        std::shared_ptr<std::vector<GLfloat>> getCurrSceneVertexData();
        void switchCurrentScene(std::string name);
        std::shared_ptr<Shader> getCurrentSceneShader();
        void update(GLFWwindow* window);
        void render();
        void printAllScenes();
        std::shared_ptr<Scene> getCurrentScene();
        std::unordered_map<std::string, std::shared_ptr<Scene>> getAllScenes();
};

#endif