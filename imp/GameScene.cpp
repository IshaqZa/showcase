#include <GameScene/GameScene.h>

void GameScene::addElement(std::string name, std::shared_ptr<GameObject> element){
    elements[name] = element;
}


void GameScene::update(GLFWwindow* window){

    glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

    if(vao == nullptr) throw std::runtime_error("VAO not initialised");
    if(vbo == nullptr) throw std::runtime_error("VBO not initialised");
    vbo->Bind();
    vao->Bind();
}

void GameScene::render(){
    glClear(GL_COLOR_BUFFER_BIT);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }
    std::cout << "background color cleared" << std::endl;
    shader->Activate();
    std::cout << "Shader activated" << std::endl;
    vao->Bind();
    std::cout << "VAO bound" << std::endl;

    if(isBackgroundImage){

        GLuint transMat = glGetUniformLocation(shader->ID, "transform");

        glUniformMatrix4fv(transMat, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

        backgroundEBO->Bind();
        backgroundImage->Bind();
        glUniform1i(isTex, 1);
        if(glCheckError() != GL_NO_ERROR){
            exit(EXIT_FAILURE);
        }

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        if(glCheckError() != GL_NO_ERROR){
            exit(EXIT_FAILURE);
        }
        backgroundImage->Unbind();
        backgroundEBO->Unbind();
    }
    
    try{
        for(const auto& x : elements){
            if(!x.second){
                throw std::runtime_error("Empty element pointer");
            }
            std::cout << "rendering: " << x.first << std::endl;
            shader->Activate();
            vao->Bind();
            x.second->update((*this->shader));
            x.second->draw(isTex);
        }
        vao->Unbind();
    }catch(std::runtime_error& e){
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

std::shared_ptr<GameObject> GameScene::getElementByName(std::string name){
    return elements[name];
}

// void GameScene::setBackground(glm::vec4 backgroundColor){
//     this->backgroundColor = backgroundColor;
// }

// void GameScene::setBackground(Texture texture, const char* texLocation, GLuint unit){
//     backgroundImage = std::make_shared<Texture>(texture);
//     backgroundImage->texUnit((*shader), texLocation, unit);
//     vertices->insert(vertices->end(), {
//             -1.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // top left
//             -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
//             1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f, // bottom right
//              1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f // top right
//         });
//     backgroundIndex = index;
//     GLuint normBackgroundIndex = backgroundIndex/9;
//     std::vector<GLuint> indices = {
//         normBackgroundIndex + 0, normBackgroundIndex + 3, normBackgroundIndex + 1,
//         normBackgroundIndex + 3, normBackgroundIndex + 1, normBackgroundIndex + 2
//     };

//     backgroundEBO = std::make_shared<EBO>(indices.data(), indices.size() * sizeof(GLuint));
//     backgroundIndex = index;

//     index += 36;
// }

// void GameScene::setBackgroundImage(bool isImage){
//     isBackgroundImage = isImage;
// }