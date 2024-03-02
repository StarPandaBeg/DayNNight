#include "Application.h"

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main()
{
    DayNNight::Application application;
    application.run();
    return 0;
}