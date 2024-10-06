#ifndef DEBUGGER_CLASS_H
#define DEBUGGER_CLASS_H

#include <glad/glad.h>
#include <iostream>

GLenum glCheckError_(const char *file, int line);

#define glCheckError() glCheckError_(__FILE__, __LINE__)

#endif