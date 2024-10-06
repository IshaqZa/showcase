#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <memory>
#include <stb/stb_image.h>
#include <Buffer/VBO.h>
#include <Buffer/VAO.h>
#include <Buffer/EBO.h>
#include <Scene/Scene.h>
#include <Scene/SceneManager.h>
#include <shader/shader.h>
#include <Buffer/texture.h>
#include <ui/ui.h>
#include <EventHandler/EventHandler.h>
#include <EventHandler/Actions.h>
#include <UI/UIBuilder.h>
#include <GameScene/GameScene.h>
#include <GameScene/GameObject.h>


using namespace std;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

GLfloat playerspeedX = 0.4f;
GLfloat playerspeedY = 1.0f;

glm::vec2 currentMove = glm::vec2(playerspeedX, 0.0f);



void framebuffer_size_callback(GLFWwindow* window, int width, int height){

    glViewport(0, 0, width, height);

}

void errorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void userInput(GLFWwindow* window, Player player){
    // currentMove = glm::vec2(0.0f, 0.0f);

    // Check each key and add corresponding movement
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        currentMove += glm::vec2(0.0f, playerspeedY);  // Move up
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        currentMove += glm::vec2(0.0f, -playerspeedY); // Move down
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        currentMove += glm::vec2(-playerspeedX, 0.0f); // Move left
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        currentMove += glm::vec2(playerspeedX, 0.0f);  // Move right
    }

    // Normalize diagonal movement if necessary
    if(currentMove != glm::vec2(0.0f)) {
        currentMove = glm::normalize(currentMove) * playerspeedX;
    }

    if((player.getPosition().x + player.getData().size.x) >= 1.06f || (player.getPosition().x) <= -1.06f){
        currentMove.x *= -1;
        std::cout << "collision detected (X-axis)" << std::endl;
    }
    if((player.getPosition().y) >= 1.06f || (player.getPosition().y - player.getData().size.y) <= -1.06f){
        currentMove.y *= -1;
        std::cout << "collision detected (Y-axis)" << std::endl;
    }
}

// void exitInput(GLFWwindow *window)
// {
//     if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
// }

// this function is purely for testing purposes
// void print(int a, int b){
//     cout << a + b << endl;
// }


std::shared_ptr<Scene2D> loadMainMenu(){
    std::shared_ptr<Scene2D> MainMenu = std::make_shared<Scene2D>();
    MainMenu->createShader("../resources/Shaders/default.vert", "../resources/Shaders/default.frag");
    MainMenu->createEventHandler();
    MainMenu->setBackground(
        glm::vec4(
            0.5f
        )
    );

    UIBuilder btnBuilder(MainMenu);
    btnBuilder.setPosition(glm::vec2(-0.89f, 0.25f))
               .setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))
               .setSize(glm::vec2(0.3f, 0.1f))
               .setRenderType(IMAGE_TYPE)
               .setTexture("../resources/textures/START.png")
               .setShape(RECTANGLE_SHAPE);
    std::shared_ptr<Button> play = btnBuilder.buildButton();

    btnBuilder.setPosition(glm::vec2(-0.89f, 0.0))
              .setTexture("../resources/textures/QUIT.png")
              .setSize(glm::vec2(0.23f, 0.1f));

    std::shared_ptr<Button> quit = btnBuilder.buildButton();
    
    
    MainMenu->addElement("play", play);
    MainMenu->addElement("quit", quit);
    
    MainMenu->addEventListener(EVENT_ON_CLICK, "play", actions::playOnClick);
    MainMenu->addEventListener(EVENT_ON_HOVER_ENTER, "play", actions::playOnHoverEnter);
    MainMenu->addEventListener(EVENT_ON_HOVER_LEAVE, "play", actions::playOnHoverLeave);

    MainMenu->addEventListener(EVENT_ON_CLICK, "quit", actions::quitOnClick);
    MainMenu->addEventListener(EVENT_ON_HOVER_ENTER, "quit", actions::quitOnHoverEnter);
    MainMenu->addEventListener(EVENT_ON_HOVER_LEAVE, "quit", actions::quitOnHoverLeave);

    MainMenu->setBackgroundImage(true);
    Texture tex("../resources/textures/mainmenu.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    MainMenu->setBackground(tex, "tex", 0);

    MainMenu->createVBO();
    MainMenu->createVAO(3, 4, 2, GL_FLOAT);
    return MainMenu;
}

std::shared_ptr<GameScene> loadGame(){
    UIFactory* factory = UIFactory::getInstance();
    factory->addType("Player", Player::create);

    std::shared_ptr<GameScene> GameContext = std::make_shared<GameScene>();

    GameContext->createShader("../resources/Shaders/default.vert", "../resources/Shaders/default.frag");

    UIBuilder playerBuilder(GameContext);

    playerBuilder.setPosition(glm::vec2(0.0f, 0.0f))
                 .setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))
                 .setSize(glm::vec2(0.2f, 0.25f))
                 .setRenderType(IMAGE_TYPE)
                 .setTexture("../resources/textures/blackhole.png")
                 .setShape(RECTANGLE_SHAPE);

    std::cout << "player object data set" << std::endl;

    std::shared_ptr<Player> player = static_pointer_cast<Player>(playerBuilder.buildElement("Player"));
    std::cout << "player object pointer created" << std::endl;

    GameContext->addElement("player", player);

    GameContext->setBackgroundImage(true);
    Texture tex("../resources/textures/space.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    GameContext->setBackground(tex, "tex", 0);

    GameContext->createVBO();
    GameContext->createVAO(3, 4, 2, GL_FLOAT);

    return GameContext;

}

int main(){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Sci Hunt", glfwGetPrimaryMonitor(), NULL);
    if(window == NULL){
        cout << "An Error occured creating the window: " << endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

        cout << "There was an error intialising GLAD" << endl;
        return EXIT_FAILURE;

    }

    glViewport(0, 0, 1920, 1080);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetErrorCallback(errorCallback);
    
    SceneManager* sceneManager = SceneManager::getInstance();

    std::shared_ptr<Scene2D> MainMenu = loadMainMenu();
    std::shared_ptr<GameScene> GameContext = loadGame();

    
    sceneManager->addScene("Game", GameContext);
    sceneManager->addScene("Main Menu", MainMenu);
    
    sceneManager->switchCurrentScene("Game");

    std::shared_ptr<Shader> gameShader = GameContext->getShaderProgram();

    GLuint transMat = glGetUniformLocation(gameShader->ID, "transform");

    std::shared_ptr<Player> player = static_pointer_cast<Player>(GameContext->getElementByName("player"));

    while(!glfwWindowShouldClose(window)){

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 

        glUniformMatrix4fv(transMat, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

        

        player->move(currentMove * deltaTime);

        try{
            std::cout << "starting scene update using scene manager" << std::endl;
            sceneManager->update(window);
            std::cout << "starting current active scene rendering" << std::endl;
            sceneManager->render();
        } catch(std::runtime_error& e){
            e.what();
        }

        userInput(window, (*player));
        glfwSwapBuffers(window);
        glfwPollEvents();
        // GLenum error = glGetError();
        // if(error) std::cout << "OpenGL Error Number:" << error << std::endl;
        // break;
    }

    glfwDestroyWindow(window);
    std::cout << "destroyed window" << std::endl;
    glfwTerminate();
    std::cout << "Terminated glfw" << std::endl;
    return EXIT_SUCCESS;
    
}