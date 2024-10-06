#ifndef UI_CLASS_H
#define UI_CLASS_H

#include <glad/glad.h>
#include <vector>
#include <functional>
#include <Buffer/texture.h>
#include <Buffer/EBO.h>
#include <memory>
#include "glm/glm.hpp"
#include "Shape.h"

enum Shapes{
    TRIANGLE_SHAPE,
    RECTANGLE_SHAPE,
    CIRCLE_SHAPE
};

class MenuElement {

    protected:
        GLuint index;
        std::string text;
        Shapes shapeValue;
        std::shared_ptr<Shape> shape;
        std::shared_ptr<Appearance2D> appearance;
        std::shared_ptr<std::vector<GLuint>> indices;
        std::shared_ptr<EBO> ebo;
        std::shared_ptr<Texture> texture;

    public:
        MenuElement(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape);
        void setPos(glm::vec2 pos);
        void setSize(glm::vec2 size);
        void setColor(glm::vec4 color);
        void updateColor(std::shared_ptr<std::vector<GLfloat>> vertices, int colorOffSet);
        void setRenderType(int renderType);
        bool contains(glm::vec2 pos);
        //this function has been made for debugging purposes
        void printData(std::shared_ptr<std::vector<GLfloat>> vertices);
        virtual void draw(GLuint texBool)=0;
        virtual void setTexture(Texture texture, Shader& shader, const char* uniform, GLuint unit)=0;

};

class Button : public MenuElement{

    private:
        

    public:
        Button(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape)
            : MenuElement(vertices, globalIndex, appearance, shape){};
        void setTexture(Texture texture, Shader& shader, const char* texLocation, GLuint unit) override;

        void draw(GLuint texBool) override;
        
};

#endif //UI_CLASS_H