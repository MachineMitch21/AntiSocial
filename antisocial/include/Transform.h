
#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include <AntiSocialDLL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace antisocial
{

    class ANTISOCIAL_API Transform
    {
    public:
        Transform();
        ~Transform();

    private:
        glm::vec3   _position;
        glm::vec3   _rotation;
        glm::vec3   _scale;
    };

}

#endif // __TRANSFORM_H__
