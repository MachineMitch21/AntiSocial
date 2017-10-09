#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include <GL/glew.h>
#include <string>
#include <iostream>

#include <Mesh.h>
#include <stb_image.h>

using antisocial::Mesh;

#define CUBE_MAP_FRONT   GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
#define CUBE_MAP_BACK    GL_TEXTURE_CUBE_MAP_POSITIVE_Z
#define CUBE_MAP_TOP     GL_TEXTURE_CUBE_MAP_POSITIVE_Y
#define CUBE_MAP_BOTTOM  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
#define CUBE_MAP_RIGHT   GL_TEXTURE_CUBE_MAP_POSITIVE_X
#define CUBE_MAP_LEFT    GL_TEXTURE_CUBE_MAP_NEGATIVE_X

namespace antisocial
{

    class Skybox
    {
    public:
        Skybox(std::string front, std::string back, std::string top, std::string bottom, std::string right, std::string left, Mesh* mesh);
        ~Skybox();

        void draw();

    private:
        bool loadSideTexture(GLenum side, std::string file);

    private:
        GLuint _cubeMapHandle;
        Mesh* _cubeMesh;
    };

}

#endif // __SKYBOX_H__
