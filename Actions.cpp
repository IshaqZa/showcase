#include "EventHandler/Actions.h"

SceneManager* sceneManager = SceneManager::getInstance();

void actions::playOnClick(){
    sceneManager->switchCurrentScene("Game");
}

void actions::quitOnClick(){
    exit(EXIT_SUCCESS);
}

void actions::playOnHoverEnter(){
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes = sceneManager->getAllScenes();
    std::cout << "Hovered Over button" << std::endl;
    if(scenes.empty()) std::cout << "Scenes is empty" << std::endl;
    std::shared_ptr<Scene2D> scene = std::static_pointer_cast<Scene2D>(scenes["Main Menu"]);
    std::cout << "Returned Main Menu Scene" << std::endl;
    std::shared_ptr<Shader> currShader = scene->getShaderProgram();
    std::cout << "Returned active shader" << std::endl;
    std::shared_ptr<MenuElement> btn = scene->getElementByName("play");
    std::cout << "Returned Play Button" << std::endl;
    Texture tex("../resources/textures/START-hover.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);

    btn->setTexture(tex, (*currShader), "tex", 0);

}

void actions::playOnHoverLeave(){
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes = sceneManager->getAllScenes();
    std::cout << "Buttoned hovered left" << std::endl;
    std::shared_ptr<Scene2D> scene = std::static_pointer_cast<Scene2D>(scenes["Main Menu"]);
    std::cout << "retrieved main menu" << std::endl;
    std::shared_ptr<Shader> currShader = scene->getShaderProgram();
    std::cout << "retrieved current active shader" << std::endl;
    std::shared_ptr<MenuElement> btn = scene->getElementByName("play");
    std::cout << "retrieved play button" << std::endl;
    Texture tex("../resources/textures/START.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    std::cout << "Created texture" << std::endl;
    btn->setTexture(tex, (*currShader), "tex", 0);
    std::cout << "set texture" << std::endl;
}

// void actions::settingsOnHoverEnter(){
//     std::unordered_map<std::string, std::shared_ptr<Scene>> scenes = sceneManager->getAllScenes();
//     std::cout << "Hovered Over button" << std::endl;
//     if(scenes.empty()) std::cout << "Scenes is empty" << std::endl;
//     std::shared_ptr<Scene2D> scene = std::static_pointer_cast<Scene2D>(scenes["Main Menu"]);
//     std::cout << "Returned Main Menu Scene" << std::endl;
//     std::shared_ptr<Shader> currShader = scene->getShaderProgram();
//     std::cout << "Returned active shader" << std::endl;
//     std::shared_ptr<MenuElement> btn = scene->getElementByName("play");
    
//     std::cout << "Returned Play Button" << std::endl;
//     Texture tex("../resources/textures/OPTIONS blue.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
//     std::cout << "Created on hover texture" << std::endl;
//     btn->setTexture(tex, (*currShader), "tex", 0);
//     std::cout << "Set the new texture into the button object" << std::endl;
// }
// void actions::settingsOnHoverLeave(){
//     std::unordered_map<std::string, std::shared_ptr<Scene>> scenes = sceneManager->getAllScenes();
//     std::cout << "Hovered Over button" << std::endl;
//     if(scenes.empty()) std::cout << "Scenes is empty" << std::endl;
//     std::shared_ptr<Scene2D> scene = std::static_pointer_cast<Scene2D>(scenes["Main Menu"]);
//     std::cout << "Returned Main Menu Scene" << std::endl;
//     std::shared_ptr<Shader> currShader = scene->getShaderProgram();
//     std::cout << "Returned active shader" << std::endl;
//     std::shared_ptr<MenuElement> btn = scene->getElementByName("play");
//     std::cout << "Returned Play Button" << std::endl;
//     Texture tex("../resources/textures/OPTIONS purple.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
//     btn->setTexture(tex, (*currShader), "tex", 0);
// }
void actions::quitOnHoverEnter(){
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes = sceneManager->getAllScenes();
    std::cout << "Hovered Over button" << std::endl;
    if(scenes.empty()) std::cout << "Scenes is empty" << std::endl;
    std::shared_ptr<Scene2D> scene = std::static_pointer_cast<Scene2D>(scenes["Main Menu"]);
    std::cout << "Returned Main Menu Scene" << std::endl;
    std::shared_ptr<Shader> currShader = scene->getShaderProgram();
    std::cout << "Returned active shader" << std::endl;
    std::shared_ptr<MenuElement> btn = scene->getElementByName("quit");
    std::cout << "Returned Play Button" << std::endl;
    Texture tex("../resources/textures/QUIT-hover.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    btn->setTexture(tex, (*currShader), "tex", 0);
}
void actions::quitOnHoverLeave(){
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes = sceneManager->getAllScenes();
    std::cout << "Hovered Over button" << std::endl;
    if(scenes.empty()) std::cout << "Scenes is empty" << std::endl;
    std::shared_ptr<Scene2D> scene = std::static_pointer_cast<Scene2D>(scenes["Main Menu"]);
    std::cout << "Returned Main Menu Scene" << std::endl;
    std::shared_ptr<Shader> currShader = scene->getShaderProgram();
    std::cout << "Returned active shader" << std::endl;
    std::shared_ptr<MenuElement> btn = scene->getElementByName("quit");
    std::cout << "Returned Play Button" << std::endl;
    Texture tex("../resources/textures/QUIT.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    btn->setTexture(tex, (*currShader), "tex", 0);
}

void actions::empty(){}