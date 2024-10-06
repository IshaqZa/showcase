#ifndef UIBUILDER_CLASS_H
#define UIBUILDER_CLASS_H

#include <memory>
#include <vector>
#include <Scene/Scene.h>
#include <ui/UIFactory.h>
class UIBuilder{

    private:
        UIFactory* uiFactory;
        std::shared_ptr<Scene> scene;
        std::shared_ptr<Texture> texture;
        glm::vec2 pos;
        glm::vec4 color;
        glm::vec2 size;
        int renderType = -1;
        Shapes shape;


    public:
        UIBuilder(std::shared_ptr<Scene> scene) : scene(scene) {};
        UIBuilder& setPosition(glm::vec2 pos);
        UIBuilder& setColor(glm::vec4 color);
        UIBuilder& setSize(glm::vec2 size);
        UIBuilder& setRenderType(int type);
        UIBuilder& setTexture(std::shared_ptr<Texture> texture);
        UIBuilder& setTexture(std::string path);
        UIBuilder& setShape(Shapes shape);
        bool checkNull();
        std::shared_ptr<MenuElement> buildElement(std::string type);
        std::shared_ptr<Button> buildButton();

};

#endif