#pragma once

#ifndef EngineAPI_H
#define EngineAPI_H

#include "gEngineCommon.h"
#include "gInput.h"
#include "gRenderMg.h"
#include <future>

class ENGINE_API Engine
{
public:

    static Engine& GetInstance();
  
    void RunApplication();

    void MainLoop();

    void Update();

    void Render();

    void ShutDownApplication();

    void AsyncLoadLevel();

    RenderManager gRenderManager;
    Input* gInputManager = nullptr;
  

private:

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    Engine();

    ~Engine();


};


#endif 