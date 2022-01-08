#include "definitions.hpp"

class Camera
{
public:
    void CameraInit(GLuint shaderProgram, GLFWwindow* window);
    void CameraUpdate(GLFWwindow* window);
    void ProcessKeyboardInput(GLFWwindow* window);
    void ProcessMouseMovement(double xoffset, double yoffset, GLboolean constrainPitch = true);

    GLuint matrixID;

    mat4 projection;          // Projection Matrix
    mat4 view;                // Camera Matrix
    mat4 model;               // Identity matrix (Model is in center of scene)

    mat4 modelViewProjection; // Final "Result"

    mat4 textProjection;

    // Camera "Physical" Settings
    float cameraFOV;
    float aspectRatio;
    float nearClipPlane;
    float farClipPlane;

    // Camera System Movement...
    vec3 worldUp;

    vec3 cameraPosition;

    vec3 cameraFront;
    vec3 cameraRight;
    vec3 cameraUp;

    vec3 cameraTarget;

    float movementSpeed;

    float horizontalAngle;
    float verticalAngle;
    float mouseSensitivity;

    float mousePositionX;
    float mousePositionY;

    double lastMouseX = SCREEN_WIDTH / 2;
    double lastMouseY = SCREEN_HEIGHT / 2;

    bool firstMouse = true;

    double yaw = -90.0f;
    double pitch = 0.0f;

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void UpdateCameraVectors()
    {
        // calculate the new Front vector
        vec3 front;
        front.x = cos(radians((float)yaw)) * cos(radians((float)pitch));
        front.y = sin(radians((float)pitch));
        front.z = sin(radians((float)yaw)) * cos(radians((float)pitch));
        cameraFront = normalize(front);
        // also re-calculate the Right and Up vector
        cameraRight = normalize(cross(cameraFront, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        cameraUp = normalize(cross(cameraRight, cameraFront));
    }
};
