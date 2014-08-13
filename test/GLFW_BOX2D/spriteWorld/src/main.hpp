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

#include "RenderGL3.h"
#include "DebugDraw.h"
#include "utils.hpp"

#endif