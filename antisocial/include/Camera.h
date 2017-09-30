#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <Vector3.h>
#include <glm/glm.hpp>

enum CAMERA_VIEW_MODE
{
    PERSPECTIVE     = 0,
    ORTHOGRAPHIC    = 1
};

class Camera
{
public:
    Camera(float fov, float x, float y, float z);

    // *******************************************************************
    // Camera class will not rely on a VECTOR3 of a certain type as of yet
    // since we do not want to keep glm forever.  This constructor will be
    // implemented when our math library is functional.
    // *******************************************************************
    // Camera(float fov, Vector3 position, Vector3 rotation);

    ~Camera();

    void setFOV(float fov);
    void setAspectRatio(float aspectRatio);
    void setNearClip(float nearClip);
    void setFarClip(float farClip);

private:
    glm::vec3 _position;
    glm::vec3 _rotation;
    float _fov;
    float _nearClip;
    float _farClip;
    enum CAMERA_VIEW_MODE _viewMode;
};

#endif // __CAMERA_H__
