#include "Camera3D.h"
#include "glm/gtc/matrix_transform.hpp"
#include <algorithm>

glm::mat4 lookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
    glm::vec3 cameraDirection = glm::normalize(eye - center);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    glm::mat4 lookAt;
    lookAt[0][0] = cameraRight.x;
    lookAt[1][0] = cameraRight.y;
    lookAt[2][0] = cameraRight.z;
    lookAt[3][0] = -eye.x;

    lookAt[0][1] = cameraUp.x;
    lookAt[1][1] = cameraUp.y;
    lookAt[2][1] = cameraUp.z;
    lookAt[3][1] = -eye.y;

    lookAt[0][2] = cameraDirection.x;
    lookAt[1][2] = cameraDirection.y;
    lookAt[2][2] = cameraDirection.z;
    lookAt[3][2] = -eye.z;

    lookAt[0][3] = 0;
    lookAt[1][3] = 0;
    lookAt[2][3] = 0;
    lookAt[3][3] = 1;

    return lookAt;
}

glm::mat4 Camera3D::GetView()
{
    return glm::lookAt(CameraPosition, CameraPosition + _cameraFront, _cameraUp);
}

glm::mat4 Camera3D::GetProjection()
{
    return glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 100.f);
}

void Camera3D::ChangePitchYaw(float xoffset, float yoffset, float deltaTime)
{
    constexpr float sensitivity = 10.f;

    _yaw += xoffset * sensitivity * deltaTime;
    _pitch += yoffset * sensitivity * deltaTime;

    _pitch = std::clamp(_pitch, -89.f, 89.f);

    glm::vec3 direction;
    direction.x = glm::cos(glm::radians(_yaw)) * glm::cos(glm::radians(_pitch));
    direction.y = glm::sin(glm::radians(_pitch));
    direction.z = glm::sin(glm::radians(_yaw)) * glm::cos(glm::radians(_pitch));
    _cameraFront = glm::normalize(direction);
}

void Camera3D::Move(CameraMoveDirection direction, float speed, float deltaTime, bool lockVertical)
{
    auto forward = _cameraFront;
    if (lockVertical)
        forward.y = 0;

    switch (direction)
    {
    case CameraMoveDirection::Forward:
        CameraPosition += forward * speed * deltaTime;
        break;
    case CameraMoveDirection::Backward:
        CameraPosition += forward * -speed * deltaTime;
        break;
    case CameraMoveDirection::Right:
        CameraPosition += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * (speed * deltaTime);
        break;
    case CameraMoveDirection::Left:
        CameraPosition += glm::normalize(glm::cross(_cameraUp, _cameraFront)) * (speed * deltaTime);
        break;
    }
}
