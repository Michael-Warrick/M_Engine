#include "../headers/display.hpp"
#include "../headers/fpsCounter.h"

int main()
{
    Display display;
    display.Init();

    /* MAIN RENDER LOOP */
    while (!glfwWindowShouldClose(display.window))
    {
        display.PrepareFrame();
        display.NextFrame();
    }

    display.Cleanup();
    return 0;
}