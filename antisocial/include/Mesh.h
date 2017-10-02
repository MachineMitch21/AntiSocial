
#ifndef __MESH_H__
#define __MESH_H__

#include <Drawable.h>

namespace antisocial
{

    class Mesh : public Drawable
    {
    public:
        Mesh();
        ~Mesh();

        void draw(bool wireframe) override;

        void setVBO(GLuint* vbo);
        void setVAO(GLuint* vao);
    private:
        GLuint* _vao;
        GLuint* _vbo;
    };

}


#endif // __MESH_H__
