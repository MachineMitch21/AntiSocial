#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

class Drawable
{
public:
    Drawable();
    virtual ~Drawable();

    virtual void draw(bool wireframe) = 0;
private:

protected:

};

#endif // __DRAWABLE_H__
