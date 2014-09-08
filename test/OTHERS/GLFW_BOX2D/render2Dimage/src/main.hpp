#ifndef _MAIN_HPP
#define _MAIN_HPP

#if defined(__APPLE__)
#include <OpenGL/gl3.h>
#else
#include <glew/glew.h>
#endif

#include <glfw/glfw3.h>
#include <stdio.h>

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

struct LFRect { GLfloat x; GLfloat y; GLfloat w; GLfloat h; };

#endif