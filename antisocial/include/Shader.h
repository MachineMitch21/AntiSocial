
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define MAX_SHADERS 2
#define ERR_LOG 512

namespace antisocial {

	class Shader
	{
	public:
		Shader(std::string* files, GLenum* types);
		Shader();
		~Shader();

		void bind();
		void unbind();
		
		GLuint& getProgram();

		void setMatrix4(const std::string& name, const float* v);
		void setVector2(const std::string& name, float v1, float v2);
		void setVector3(const std::string& name, float v1, float v2, float v3);
		void setVector4(const std::string& name, float v1, float v2, float v3, float v4);
		void setFloat(const std::string& name, float v);
		void setBool(const std::string& name, bool v);
		void setInteger(const std::string& name, int v);
		void setUInteger(const std::string& name, unsigned int v);

	private:
		void link_program();
		GLuint compile_shader(const std::string& shader_src, GLenum shader_type);
		std::string load_shader(const std::string& filename);

	private:
		GLuint _shaders[MAX_SHADERS];
		GLuint _handle;
		GLint _success;
		GLchar _errLog[ERR_LOG];
	};

}
