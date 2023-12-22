
#include "Engine/gEngine/gEngine.h"


Engine& engine = Engine::GetInstance();

int main(int argc, const char* argv[])
{
    
    //LOG.Log(Logger::LogLevel::Error,("Failed to initialize GLAD"));
    engine.RunApplication();



    return 0;
}