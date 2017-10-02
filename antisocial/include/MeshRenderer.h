
#ifndef __MESHRENDERER_H__
#define __MESHRENDERER_H__

#include <Mesh.h>

using antisocial::Mesh;

namespace antisocial
{

    class MeshRenderer
    {
    public:
        MeshRenderer();
        ~MeshRenderer();

        void renderMesh(const Mesh& mesh);

    private:

    };

}

#endif // __MESHRENDERER_H__
