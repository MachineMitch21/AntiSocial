#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

#include <GL/glew.h>

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind();
    void unbind();
private:
    GLint _handle;
};

#endif // __VERTEXARRAY_H__
