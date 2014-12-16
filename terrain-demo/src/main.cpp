
#include "application.h"
#include "renderer.h"


//
//      main launcher
//
int main(int, char const**)
{
    Application *app = new Application();
    app->onInit();
    app->startMainLoop();
    app->onClose();
    
    delete app;
}