#include "../headers/fpsCounter.h"

void FPS_Counter::FPS_Counter_Init()
{
    lastTime = glfwGetTime();
    numberOfFrames = 0;
}

void FPS_Counter::FPS_Counter_Update()
{
    currentTime = glfwGetTime();
    numberOfFrames++;

    if (currentTime - lastTime >= 1.0f)
    {
        FPS_Calculate_MsPerFrame(numberOfFrames);

        FPS_Calculate_FramesPerSecond(msPerFrame);

        numberOfFrames = 0;
        lastTime += 1.0f;
    }
}

void FPS_Counter::FPS_Calculate_MsPerFrame(int numberOfFrames)
{
    // Calculates ms/frame
    msPerFrame = 1000.0 / double(numberOfFrames);
    std::cout << "\r" << msPerFrame << " ms/frame  ";
}

void FPS_Counter::FPS_Calculate_FramesPerSecond(double msPerFrame)
{
    // Converts ms/frame to frames/second
    framesPerSecond = 1 / (msPerFrame / 1000.0);
    std::cout << framesPerSecond << " FPS";
}

void FPS_Counter::FPS_Counter_Destroy()
{
    FPS_Counter::~FPS_Counter();
}