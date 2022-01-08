#include "display.hpp"
#include "fpsCounter.h"

int main()
{
    Display display;
    FPS_Counter fpsCounter;

    display.Init();
    fpsCounter.FPS_Counter_Init();

    /* MAIN RENDER LOOP */
    while (!glfwWindowShouldClose(display.window))
    {
        display.PrepareFrame();

        fpsCounter.FPS_Counter_Update();

        display.NextFrame();
    }

    display.Cleanup();

    return 0;
}