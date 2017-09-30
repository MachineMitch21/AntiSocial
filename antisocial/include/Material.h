
#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <memory>

#include <Shader.h>
namespace antisocial
{

    class Material
    {
    public:
        Material(std::shared_ptr<Shader> shader);
        Material();
        ~Material();

        inline bool hasShader() { return (_shader ? true : false); }
        inline const Shader& getShader() const { return *_shader; };
    private:
        std::shared_ptr<Shader> _shader;
    };

}

#endif // __MATERIAL_H__
