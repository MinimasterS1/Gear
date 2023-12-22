#pragma once


#include "gCamera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern GLFWwindow* window;

extern Camera camera;
extern int SCR_WIDTH, SCR_HEIGHT;

extern float DragStep;

extern bool EditorMode;

extern bool GameConsole;