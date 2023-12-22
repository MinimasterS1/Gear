#pragma once

#include "Engine/gEngine/gEngineCommon.h"
#include "gCore.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <functional>
#include <filesystem>

#include "iostream"



class ENGINE_API EditorAPI {

public:

    EditorAPI();

    EditorAPI(GLFWwindow* window, const char* text);

    ~EditorAPI();


    void RenderEditor();

    void RenderConsole();

    void DrawFrameBuffer();

    int w;
    int h;

    GLFWwindow* m_Window;


    void WindowScale(GLFWwindow* window, int* width, int* height);

    void DrawPanel(const char* name, ImVec2 position, ImVec2 size, std::function<void()> contentFunc);


    int  getWidth();

    int getHeight();

    int getXoffset();

    int getYoffset();

    void setWidth(int width);

    void setHeight(int height);


private:


    const char* m_Text;

   int RenderPanelWidth = 1580;
   int RenderPanelHeight = 1090;
   int Offset_X = 0;
   int Offset_Y = 150;

   bool ShowLoadFileDialog = false;
   bool ShowSaveFileDialog = false;







};




