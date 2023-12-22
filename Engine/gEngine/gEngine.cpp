#include "gEngine.h"

Engine::Engine()
{

}

Engine::~Engine()
{

}


Engine& Engine::GetInstance()
{
    static Engine instance; // Создается только один раз
    return instance;
}

void Engine::RunApplication()
{
    gRenderManager.startUp();
    gInputManager = new Input(camera);

    // resources.PreloadResources();

     //resources.LoadLevel();

    MainLoop();
}

void Engine::MainLoop()
{

  while (!gRenderManager.ShouldClose()) {

    Update();

    Render();
}

}

void Engine::Update()
{
    gRenderManager.update();
}

void Engine::Render()
{
    gRenderManager.Render();
}


void Engine::ShutDownApplication()
{
    gRenderManager.shutDown();
    delete gInputManager;
    gInputManager = nullptr;
}

void Engine::AsyncLoadLevel()
{
}


