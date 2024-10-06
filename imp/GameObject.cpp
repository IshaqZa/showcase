#include <GameScene/GameObject.h>

void Player::setTexture(Texture texture, Shader& shader, const char* uniform, GLuint unit){
    
    this->texture = std::make_shared<Texture>(texture);
    this->texture->texUnit(shader, uniform, unit);
}

void Player::draw(GLuint texBool){

     if(!appearance || !shape || !ebo) {
        std::cerr << "Error drawing button due to initialised data" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Binding texture" << std::endl;
    if(appearance->renderType == IMAGE_TYPE) {
        this->texture->Bind();
    }
    std::cout << "Setting render type" << std::endl;
    glUniform1i(texBool, appearance->renderType);
    try{
        std::cout << "Binding EBO" << std::endl;
        ebo->Bind();
    } catch(std::runtime_error& e){

        std::cerr << "Error: " << e.what() << std::endl;

    } catch(std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    std::cout << "calling draw from shape object" << std::endl;
    shape->draw();

    std::cout << "Unbinding texture and ebo" << std::endl;
    if(appearance->renderType == IMAGE_TYPE) {
        this->texture->Unbind();
    }
    // ebo->Unbind();
    std::cout << "Unbinding done" << std::endl;
}

std::shared_ptr<MenuElement> Player::create(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape) {
    std::cout << "creating element shared pointer" << std::endl;
    return std::make_shared<Player>(vertices, globalIndex, appearance, shape);
}

void Player::move(glm::vec2 translate){

    std::cout << "Current player position ( " << position.x << ", " << position.y << ")" << std::endl;

    model = glm::translate(model, glm::vec3(translate, 0.0f));

    position += translate;

    std::cout << "New player position ( " << position.x << ", " << position.y << ")" << std::endl;


}

void Player::rotate(GLfloat angle, bool isClockwise){
    if(!isClockwise) {
        angle = 360.0f - angle;
    }

    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Player::scale(glm::vec2 scale){
    model = glm::scale(model, glm::vec3(scale, 1.0f));
}

void Player::update(Shader& shader){
    GLuint transMat = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transMat, 1, GL_FALSE, glm::value_ptr(model));
}

glm::vec2 Player::getPosition(){
    return position;
}

Appearance2D Player::getData(){
    return (*this->appearance);
}