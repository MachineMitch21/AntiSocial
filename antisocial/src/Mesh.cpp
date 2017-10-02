
#include <Mesh.h>

using antisocial::Mesh;

Mesh::Mesh(float* vertices, int numVertices)
    :   Drawable(),
        _vertices(vertices),
        _numVertices(numVertices)
{

}

Mesh::~Mesh()
{

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
        //glBindVertexArray(*_vao);
        glBindBuffer(GL_ARRAY_BUFFER, *_vbo);
        glDrawArrays(GL_TRIANGLES, 0, _numVertices);
    }
}
