#include <vector>
#include <memory>
#include "glad/glad.h"
#include <ui/Appearance.h>

class Shape {

protected:
    std::shared_ptr<std::vector<GLfloat>> vertices;
    std::shared_ptr<std::vector<GLuint>> indices;

public:
    
    virtual void generateVertices(std::shared_ptr<Appearance2D> appearance) = 0;
    virtual void generateIndices(GLuint index) = 0;
    virtual void draw() = 0;
    
};

class Square : public Shape{
    public:
        Square(std::shared_ptr<std::vector<GLfloat>> vertices, std::shared_ptr<std::vector<GLuint>> indices);
        void generateVertices(std::shared_ptr<Appearance2D> appearance) override;
        void generateIndices(GLuint index) override;
        void draw() override;
};