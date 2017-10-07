
#include <Camera.h>

#include <iostream>

using antisocial::Camera;
using namespace antisocial::input;

Camera::Camera(float fov, float x, float y, float z, float aspectRatio, float nearClip, float farClip)
    :   _fov(fov),
        _position(glm::vec3(x, y, z)),
        _rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
        _front(glm::vec3(0.0f, 0.0f, -1.0f)),
        _up(glm::vec3(0.0f, 1.0f, 0.0f)),
        _worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
        _aspectRatio(aspectRatio),
        _nearClip(nearClip),
        _farClip(farClip),
        _yaw(-90.0f),
        _pitch(0.0f),
        _movementSpeed(5.0f)
{

}

Camera::~Camera()
{

}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(_position, _position + _front, _up);
}

void Camera::setFOV(float fov)
{
    _fov = fov;
}

void Camera::setAspectRatio(float aspectRatio)
{
    _aspectRatio = aspectRatio;
}

void Camera::setNearClip(float nearClip)
{
    _nearClip = nearClip;
}

void Camera::setFarClip(float farClip)
{
    _farClip = farClip;
}

float Camera::getFOV()
{
    return _fov;
}

float Camera::getAspectRatio()
{
    return _aspectRatio;
}

float Camera::getNearClip()
{
    return _nearClip;
}

float Camera::getFarClip()
{
    return _farClip;
}

void Camera::move(glm::vec3 direction, float speedMultiplier, float xOffset, float yOffset, float deltaTime, bool constrain)
{
    float velocity = (_movementSpeed * speedMultiplier) * deltaTime;
    _position += direction * velocity;

    xOffset *= Input::LookSensitivity;
    yOffset *= Input::LookSensitivity;

    _yaw += xOffset;
    _pitch += yOffset;

    if (constrain)
    {
        if (_pitch > 89.0f)
        {
            _pitch = 89.0f;
        }
        if (_pitch < -89.0f)
        {
            _pitch = -89.0f;
        }
    }

    glm::vec3 front;

    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front  = glm::normalize(front);

    _right  = glm::normalize(glm::cross(_front, _worldUp));
    _up     = glm::normalize(glm::cross(_right, _front));
}
