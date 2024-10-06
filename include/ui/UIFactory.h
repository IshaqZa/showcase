#ifndef UIFACTORY_CLASS_H
#define UIFACTORY_CLASS_H

#include <map>
#include <functional>
#include <string>
#include <ui/ui.h>

class UIFactory{

    private:
        std::unordered_map<std::string, std::function<std::shared_ptr<MenuElement>(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape)>> registry;
        static UIFactory* instance;
        UIFactory(){};
    public:
        UIFactory(const UIFactory& obj) = delete;
        void addType(std::string typeName, std::function<std::shared_ptr<MenuElement>(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape)> func);
        std::shared_ptr<MenuElement> create(std::string type, std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape);
        static UIFactory* getInstance();

};

#endif