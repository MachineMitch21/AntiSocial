
#ifndef __MESH_H__
#define __MESH_H__

#include <AntisocialDLL.h>

#include <Drawable.h>
#include <Shader.h>

namespace antisocial
{

    class ANTISOCIAL_API Mesh : public Drawable
    {
    public:
        Mesh(unsigned int numVertices);
        Mesh(unsigned int numVertices, Shader* shader);
        ~Mesh();

        void draw(bool wireframe) override;

        void setShader(Shader* shader);
        void setVBO(GLuint* vbo);
        void setVAO(GLuint* vao);
    private:
        Shader*         _shader;
        unsigned int    _numVertices;
        GLuint*         _vao;
        GLuint*         _vbo;
    };

}


#endif // __MESH_H__
