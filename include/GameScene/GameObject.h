#ifndef GAMEOBJECT_CLASS_H
#define GAMEOBJECT_CLASS_H

#include <ui/ui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
struct Transform {
    glm::vec2 translate;
    GLfloat rotate;
    glm::vec2 scale;
};

class GameObject : public MenuElement{


    public:
        GameObject(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape)
        : MenuElement(vertices, globalIndex, appearance, shape){};
        virtual void draw(GLuint texBool) override = 0;
        virtual void setTexture(Texture texture, Shader& shader, const char* uniform, GLuint unit) override = 0;
        virtual void update(Shader& shader) = 0;
};

class Player : public GameObject {
    private:
        Transform transformation;
        glm::vec2 position;
        glm::mat4 model = glm::mat4(1.0f);
    public:
        Player(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape)
        : GameObject(vertices, globalIndex, appearance, shape) {
            transformation.translate = glm::vec2(0.0f);
            transformation.rotate = 0.0f;
            transformation.scale = glm::vec2(1.0f);
            position = glm::vec2(0.0f);
        };
        void draw(GLuint texBool) override;
        void setTexture(Texture texture, Shader& shader, const char* uniform, GLuint unit) override;
        static std::shared_ptr<MenuElement> create(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape);

        void move(glm::vec2 translate);
        void rotate(GLfloat angle, bool isClockwise);
        void scale(glm::vec2 scale);

        glm::vec2 getPosition();
        
        Appearance2D getData();
        void update(Shader& shader) override;
};

#endif