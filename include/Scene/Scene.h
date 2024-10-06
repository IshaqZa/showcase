#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <ui/ui.h>
#include <Buffer/VBO.h>
#include <Buffer/VAO.h>
#include <shader/shader.h>
#include <EventHandler/EventHandler.h>
#include <EventHandler/EventType.h>

class EventHandler;

class Scene {

    protected:
        GLuint index = 0;
        GLuint backgroundIndex = 0;
        GLuint isTex = 0;
        std::shared_ptr<EBO> backgroundEBO;
        std::shared_ptr<VBO> vbo;
        std::shared_ptr<VAO> vao;
        std::shared_ptr<Shader> shader;
        std::shared_ptr<std::vector<GLfloat>> vertices;
        std::shared_ptr<std::vector<GLuint>> backgroundIndices;
        glm::vec4 backgroundColor;
        std::shared_ptr<Texture> backgroundImage;
        bool isBackgroundImage = false;
    
    public:
        Scene() {
            vertices = std::make_shared<std::vector<GLfloat>>();
        }
        unsigned int* currentIndex();
        void activate();
        void linkVBO(std::shared_ptr<VBO> vbo);
        void linkVAO(std::shared_ptr<VAO> vao);
        void linkShader(std::shared_ptr<Shader> shader);
        void setBackground(glm::vec4 backgroundColor);
        void setBackground(Texture texture, const char* texLocation, GLuint unit);
        void setBackgroundImage(bool isImage);
        std::shared_ptr<std::vector<GLfloat>> getVertices();
        void createVBO();
        void createVAO(int posSize, int colorSize, int texSize, GLenum type);
        std::shared_ptr<Shader> createShader(const char* vertexFile, const char* fragmentFile);
        std::shared_ptr<Shader> getShaderProgram();
        virtual void update(GLFWwindow* window) = 0;
        virtual void render() = 0;
};

class Scene2D : public Scene{

    private:
        std::shared_ptr<EventHandler> events;
        std::unordered_map<std::string, std::shared_ptr<MenuElement>> elementArray;

    public:
        Scene2D(){
            
            std::cout << "isTex loaded" << std::endl;
            if(isTex < 0) {
                std::cout << "Error retrieving tex bool" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        void createEventHandler();
        void addEventListener(EventType eventType, std::string elementName, std::function<void()> action);
        std::shared_ptr<MenuElement> getElementByName(std::string name);
        void addElement(std::string name, std::shared_ptr<MenuElement> element);
        void render() override;
        void update(GLFWwindow* window) override;
};

#endif //SCENE_CLASS_H