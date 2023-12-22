#include "gRenderMg.h"
#include "gCore.h"
#include "gTemplate.h"
#include "gMemory.h"


float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

bool firstMouse = true;

MemoryPool RenderMemory(800, 1024);


RenderManager::RenderManager()
{
    bool RenderInit = true;

    if (RenderInit)
    {
      
    }
}

RenderManager::~RenderManager()
{

}

void RenderManager::startUp()
{
    CreateWindow();
   
}

void RenderManager::shutDown()
{
    glfwMakeContextCurrent(window);
    glfwDestroyWindow(window);
    glfwTerminate();
}

void RenderManager::update()
{
    glfwPollEvents();
}

void RenderManager::framebuffer_size_callback_static(GLFWwindow* window, int width, int height)
{
    {
        RenderManager* render = static_cast<RenderManager*>(glfwGetWindowUserPointer(window));
        if (render)
        {
            render->framebuffer_size_callback(window, width, height);
        }
    }
}

void RenderManager::CreateWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    MonitorScale(&SCR_WIDTH, &SCR_HEIGHT);
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Engine", NULL, NULL);
    if (window == NULL)
    {
        LOG.Log(Logger::LogLevel::Error, "Failed to create GLFW window");
        glfwTerminate();
        return;
    }

    glfwSetWindowPos(window, 0, 25);
    glfwSetWindowUserPointer(window, this);
    glfwMakeContextCurrent(window);
   
    input= new Input(camera);
    input->startUp();

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
        static_cast<RenderManager*>(glfwGetWindowUserPointer(window))->input->MouseCallback(window, x, y);
        });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
        static_cast<RenderManager*>(glfwGetWindowUserPointer(window))->input->ScrollCallback(window, xoffset, yoffset);
        });

    glfwSetFramebufferSizeCallback(window, RenderManager::framebuffer_size_callback_static);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      // LOG.Log(Logger::LogLevel::Error, "Failed to initialize GLAD");
        return;
    }

    glEnable(GL_DEPTH_TEST);


}


void RenderManager::Render()
{
    float currentFrame = glfwGetTime();
    DeltaTime = currentFrame - LastFrame;
    LastFrame = currentFrame;
    FPS = 1.0f / DeltaTime;
  
    input->update(window, DeltaTime);
   

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

  
    glfwSwapBuffers(window);
    return;
}



void RenderManager::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void RenderManager::GL_Check(const char* label)
{
    {
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            const char* errorStr;
            switch (err) {
            case GL_INVALID_ENUM: errorStr = "GL_INVALID_ENUM"; break;
            case GL_INVALID_VALUE: errorStr = "GL_INVALID_VALUE"; break;
            case GL_INVALID_OPERATION: errorStr = "GL_INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY: errorStr = "GL_OUT_OF_MEMORY"; break;
            default: errorStr = "Unknown Error"; break;
            }

            double errorDouble = static_cast<double>(err);

            std::string errorMessage = "OpenGL Error [" + std::string(label) + "]: " + errorStr;

        //   LOG.Log(Logger::LogLevel::Error, errorMessage, errorDouble);
            std::cerr << errorMessage << std::endl;
        }
    }
}

bool RenderManager::ShouldClose()
{
    
    return glfwWindowShouldClose(window);
    
}

bool fileExists(const std::string& filename)
{
    std::ifstream file(filename);
    return file.good();
}

void RenderManager::CycleLogo()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0.5f, 0.8f, 0.7f, 1.0f);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void RenderManager::CreateSmallWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    MonitorScale(&SCR_WIDTH, &SCR_HEIGHT);
    int ScaleX = SCR_WIDTH;
    int ScaleY = SCR_HEIGHT;

    window = glfwCreateWindow(700, 300, "Main Window", NULL, NULL);
    if (window == NULL)
    {
       // LOG.Log(Logger::LogLevel::Error, "Failed to create GLFW main window");
        glfwTerminate();
        return;
    }

    int xPosition = static_cast<int>(SCR_WIDTH / 3.0f);
    int yPosition = static_cast<int>(SCR_HEIGHT / 2.5f);
    glfwSetWindowPos(window, xPosition, yPosition);

    glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);

    return;
}