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

void GameObject::move(glm::vec2 translate){

    std::cout << "Current player position ( " << position.x << ", " << position.y << ")" << std::endl;

    model = glm::translate(model, glm::vec3(translate, 0.0f));

    position += translate;

    std::cout << "New player position ( " << position.x << ", " << position.y << ")" << std::endl;


}

void GameObject::rotate(GLfloat angle, bool isClockwise){
    if(!isClockwise) {
        angle = 360.0f - angle;
    }

    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
}

void GameObject::scale(glm::vec2 scale){
    model = glm::scale(model, glm::vec3(scale, 1.0f));
}

void Player::update(Shader& shader){
    GLuint transMat = glGetUniformLocation(shader.ID, "transform");

    std::cout << "model matrix in update function:" << std::endl;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            std::cout << model[i][j] << ", ";
        }
        std::cout << "\n";
    }

    glUniformMatrix4fv(transMat, 1, GL_FALSE, glm::value_ptr(model));
}

glm::vec2 GameObject::getPosition(){
    return position;
}

Appearance2D GameObject::getData(){
    return (*this->appearance);
}

void Player::reset(){
    model = glm::mat4(1.0f);
    position = glm::vec2(0.0f);
    std::cout << "model matrix in reset function:" << std::endl;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            std::cout << model[i][j] << ", ";
        }
        std::cout << "\n";
    }
    
}

void Player::snap(int x, int y){

    model = glm::mat4(1.0f);
    
    if(x == -1){
        move(glm::vec2(-0.9f, position.y));
    }
    else if(x == 1){
        move(glm::vec2(0.9f, position.y));
    }
    if(y == -1){
        move(glm::vec2(position.x, -0.9f));
    }
    else if(y == 1){
        move(glm::vec2(position.x, 0.9f));
    }

}

void Planet::resetPosition(Texture planets[4], Shader& shader){
    

    std::random_device planetrd;
    std::mt19937 planetGen(planetrd());

    std::uniform_int_distribution<> planetDistr(0, 4);
    Texture planet = planets[planetDistr(planetGen)];

    this->setTexture(planet, shader, "tex", 0);

    model = glm::mat4(1.0f);
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> distr(-0.8f, 0.8f);

    GLfloat randomX = distr(gen);
    GLfloat randomY = distr(gen);

    position = glm::vec2(randomX, randomY);
    std::cout << "X: " << randomX << std::endl;
    std::cout << "Y: " << randomY << std::endl;

    model = glm::translate(model, glm::vec3(position, 0.0f));

}

void Planet::draw(GLuint texBool){
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

void Planet::setTexture(Texture texture, Shader& shader, const char* uniform, GLuint unit){
    this->texture = std::make_shared<Texture>(texture);
    this->texture->texUnit(shader, uniform, unit);
}

void Planet::update(Shader& shader){
    GLuint transMat = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transMat, 1, GL_FALSE, glm::value_ptr(model));
}

std::shared_ptr<MenuElement> Planet::create(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape){
    return std::make_shared<Planet>(vertices, globalIndex, appearance, shape);
}


void HealthBar::draw(GLuint texBool){
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

void HealthBar::setTexture(Texture texture, Shader& shader, const char* uniform, GLuint unit){
    this->texture = std::make_shared<Texture>(texture);
    this->texture->texUnit(shader, uniform, unit);
}

void HealthBar::update(Shader& shader){
    GLuint transMat = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transMat, 1, GL_FALSE, glm::value_ptr(model));
}

std::shared_ptr<MenuElement> HealthBar::create(std::shared_ptr<std::vector<GLfloat>> vertices, GLuint* globalIndex, std::shared_ptr<Appearance2D> appearance, Shapes shape){
    return std::make_shared<HealthBar>(vertices, globalIndex, appearance, shape);
}

GLfloat HealthBar::drain(GLfloat deltaTime){

    model = glm::mat4(1.0f);

    health -= deathRate * deltaTime;

    std::cout << "current Health: " << health << std::endl;

    GLfloat newSize = (health * 2) - 1;

    move(glm::vec2(-0.85, -0.85));

    scale(glm::vec2(newSize, 1.0f));
    return newSize;

}

void HealthBar::reset(){
    health = 1.0f;
}