
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define MAX_SHADERS 2
#define ERR_LOG 512

class Shader
{
public:
	Shader(std::string* files, GLenum* types);
	~Shader();

	void bind();
	GLuint& getProgram();

private:
	void link_program();
	GLuint compile_shader(const std::string& shader_src, GLenum shader_type);
	std::string load_shader(const std::string& filename);

private:
	GLuint m_shaders[MAX_SHADERS];
	GLuint m_program;
	GLint success;
	GLchar err_log[ERR_LOG];
};

