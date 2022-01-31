#include "../headers/display.hpp"

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