#ifndef APPEARANCE_CLASS_H
#define APPEARANCE_CLASS_H

#include <iostream>
#include <glad/glad.h>
#include <vector>
#include <Buffer/EBO.h>
#include <Buffer/texture.h>
#include "glm/glm.hpp"

#define RGBA_TYPE 0
#define IMAGE_TYPE 1

struct Appearance2D
{
  glm::vec2 position;
  glm::vec2 size;
  glm::vec4 color;
  int renderType;

  Appearance2D(glm::vec2 position, glm::vec2 size, glm::vec4 color, int renderType = RGBA_TYPE)
      : position(position), color(color), renderType(renderType), size(size) {}

};

#endif