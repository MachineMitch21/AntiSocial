#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include <GL/glew.h>

namespace antisocial
{

    class Drawable
    {
    public:
        Drawable();
        virtual ~Drawable();

        virtual void draw(bool wireframe) = 0;
    private:

    protected:

    };

}

#endif // __DRAWABLE_H__
