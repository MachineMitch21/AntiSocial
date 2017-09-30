
#include <Material.h>

using antisocial::Material;

Material::Material(std::shared_ptr<Shader> shader)
    :   _shader(shader)
{

}

Material::Material()
    :   _shader(NULL)
{

}

Material::~Material()
{

}
