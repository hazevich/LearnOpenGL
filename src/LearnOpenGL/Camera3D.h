#pragma once
#include <glm/glm.hpp>

enum CameraMoveDirection
{
    Forward, Backward, Left, Right
};

class Camera3D
{
public:
    glm::vec3 CameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::mat4 GetView();
    glm::mat4 GetProjection();

    void ChangePitchYaw(float xoffset, float yoffset, float deltaTime);

    void Move(CameraMoveDirection direction, float speed, float deltaTime, bool lockVertical = false);

private:
    glm::vec3 _cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 _cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    float _yaw = -90.0f;
    float _pitch = 0.0f;
};

