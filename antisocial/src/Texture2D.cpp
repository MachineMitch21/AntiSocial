
#include <Texture2D.h>

#include <iostream>

using antisocial::Texture2D;

Texture2D::Texture2D(const std::string& texturePath)
{
	glGenTextures(1, &_handle);
	glBindTexture(GL_TEXTURE_2D, _handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	setImage(texturePath, 0);
}

Texture2D::~Texture2D()
{
	stbi_image_free(_data);
	glDeleteTextures(1, &_handle);
}

void Texture2D::bind(unsigned int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, _handle);
}

void Texture2D::setImage(const std::string& path, unsigned int unit)
{
	bind(0);
	_data = stbi_load(path.c_str(), &_width, &_height, &_numComponents, 4);

	if (_data == NULL)
	{
		std::cerr << "Texture2D (" << path << ") was not loaded successfully" << std::endl;
		stbi_image_free(_data);
		return;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data);
	glBindTexture(GL_TEXTURE_2D, 0);
}
