#include "../headers/definitions.hpp"

class FPS_Counter {

public:
    int numberOfFrames;

    double lastTime;
    double currentTime;

    double msPerFrame;
    double framesPerSecond;

    void FPS_Counter_Init();
    void FPS_Counter_Update();
    void FPS_Counter_Destroy();
private:
    void FPS_Calculate_MsPerFrame(int numberOfFrames);
    void FPS_Calculate_FramesPerSecond(double msPerFrame);
};
