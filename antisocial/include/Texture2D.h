#ifndef __TEXTURE2D_H__
#define __TEXTURE2D_H__

#include <string>
#include <GL/glew.h>
#include <stb_image.h>

namespace antisocial {

	class Texture2D {

	public:
		Texture2D(const std::string& texturePath);
		~Texture2D();

		void bind(unsigned int unit);
		void setImage(const std::string& path, unsigned int unit);
		inline GLuint getHandle() const { return _handle; };

	private:
		int 	_height;
		int 	_width;
		int		_numComponents;
		GLuint 	_handle;
		unsigned char* _data;
	};


}

#endif // __TEXTURE2D_H__
