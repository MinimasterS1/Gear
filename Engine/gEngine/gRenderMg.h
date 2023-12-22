#pragma once

#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H


#include "gEngineCommon.h"
#include "gInput.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>


extern float LastX;
extern float LastY;
extern bool FirstMouse;


bool fileExists(const std::string& filename);

class ENGINE_API RenderManager

{
public:

    RenderManager();
    

    ~RenderManager();
 

   
    void startUp();

    void shutDown();

    void update();

    static void framebuffer_size_callback_static(GLFWwindow* window, int width, int height);

    void CreateWindow();

    void CreateSmallWindow();

    void CycleLogo();

    void Render();

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    void GL_Check(const char* label);

    void swap_buffers() { glfwSwapBuffers(window); }

    void close() { glfwSetWindowShouldClose(window, 1); }

    GLFWwindow* get_glfw_window_handle() { return window; };

    bool should_close() const { return !!glfwWindowShouldClose(window); }

    int get_window_attrib(int attrib) const { return glfwGetWindowAttrib(window, attrib); }


     float getFPS() {
        return FPS;
    }


     bool ShouldClose();

     bool IsDrawLogo = false;

  
    Input* input;
private: 

  
  
    float FPS;
    float DeltaTime;
    float LastFrame;


};

#define GL_CHECK(stmt) do { \
        stmt; \
        CheckOpenGLError(#stmt, __FILE__, __LINE__); \
    } while (0)


#endif

