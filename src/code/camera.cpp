#include "camera.hpp"

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void Camera::CameraInit(GLuint shaderProgram, GLFWwindow* window)
{
    // ModelViewProjection Uniform Handle
    matrixID = glGetUniformLocation(shaderProgram, "MVP");
    //UITextShaderID = glGetUniformLocation(fontShaderProgram, "textProjection");

    cameraFOV = 90.0f;
    aspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
    nearClipPlane = 0.01f; // Limit this to go no smaller than 0.01
    farClipPlane = 100.0f;

    worldUp = vec3(0.0f, 1.0f, 0.0f);        // World Space Up Vector, Inverse it (-1.0f) and the world flips

    cameraPosition = vec3(0.0f, 0.0f, 5.0f); // Where the camera is in World Coordinates

    cameraFront = vec3(0.0f, 0.0f, -1.0f);    // Camera's front vector with -1 om the Z axis
    cameraRight = normalize(cross(cameraFront, worldUp));
    cameraUp = normalize(cross(cameraFront, cameraRight));

    cameraTarget = vec3(0.0f, 0.0f, 0.0f);    // Where the camera wants to look at

    // Model matrix (an identity matrix seeing as the model will be at the origin)
    model = mat4(1.0f);
}

void Camera::CameraUpdate(GLFWwindow* window)
{
    float currentFrame = (float)glfwGetTime();

    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Projection Matrix (Perspective)
    projection = perspective(radians(cameraFOV), aspectRatio, nearClipPlane, farClipPlane);

    //textProjection = ortho(0.0f, (float)SCREEN_WIDTH, 0.0f, (float)SCREEN_HEIGHT);

    // Camera Matrix
    view = lookAt(cameraPosition, cameraPosition + cameraFront, worldUp);

    // Our ModelViewProjection matrix, the combination (multiplication) of our 3 matices...
    modelViewProjection = projection * view * model;

    // Send transformation to currently bound shader in MVP uniform
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &modelViewProjection[0][0]);
}

void Camera::ProcessKeyboardInput(GLFWwindow* window)
{
    movementSpeed = 5.0f * deltaTime;

    // Sprinting - Needs to be declared first ...
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        movementSpeed = movementSpeed * 2.0f;

        cameraFOV = 110.0f;

        // Some pretty cool camera shake there...
        // cameraFOV = mMath.Lerp(90.0f, 110.0f, 100.0f * deltaTime);
    }

    else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
    {
        cameraFOV = 90.0f;
    }

    // Forwards
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPosition += movementSpeed * cameraFront;
    }

    // Backwards
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPosition -= movementSpeed * cameraFront;
    }

    // Strafe Left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPosition -= cameraRight * movementSpeed;
    }

    // Strafe Right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPosition += cameraRight * movementSpeed;
    }

    // Flying Up
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        cameraPosition += movementSpeed * worldUp;
    }

    // Flying Down
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        cameraPosition -= movementSpeed * worldUp;
    }

    // ZOOM
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        cameraFOV = 45.0f;
    }


}

void Camera::ProcessMouseMovement(double xoffset, double yoffset, GLboolean constrainPitch)
{
    mouseSensitivity = 0.1f;

    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    UpdateCameraVectors();
}
