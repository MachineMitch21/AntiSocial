
#include <Mesh.h>

#include <iostream>

using antisocial::Mesh;

Mesh::Mesh(unsigned int numVertices)
    :   Drawable(),
        _shader(NULL),
        _numVertices(numVertices),
        _vao(NULL),
        _vbo(NULL)
{
}

Mesh::Mesh(unsigned int numVertices, Shader* shader)
    :   Drawable(),
        _shader(shader),
        _numVertices(numVertices),
        _vao(NULL),
        _vbo(NULL)
{
}

Mesh::~Mesh()
{

}

void Mesh::setShader(Shader* shader)
{
    _shader = shader;
}

void Mesh::setVBO(GLuint* vbo)
{
    _vbo = vbo;
}

void Mesh::setVAO(GLuint* vao)
{
    _vao = vao;
}

void Mesh::draw(bool wireframe)
{
    glPolygonMode(GL_FRONT_AND_BACK, (wireframe ? GL_LINE : GL_FILL));

    if (_vao != NULL || _vbo != NULL)
    {
        glBindVertexArray(*_vao);
        glBindBuffer(GL_ARRAY_BUFFER, *_vbo);
        glDrawArrays(GL_TRIANGLES, 0, _numVertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}
