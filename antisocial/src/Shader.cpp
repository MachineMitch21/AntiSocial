#include "Shader.h"

Shader::Shader(std::string* files, GLenum* types)
{
	m_program = glCreateProgram();

	for (int i = 0; i < MAX_SHADERS; i++) {
		m_shaders[i] = compile_shader(load_shader(files[i]), types[i]);
	}

	link_program();
}

void Shader::bind() {
	glActiveTexture(GL_TEXTURE0);
	glUseProgram(m_program);
}

GLuint& Shader::getProgram() {
	return m_program;
}

void Shader::link_program() {

	//Attach shaders to newly create program and then link everything
	for (int i = 0; i < MAX_SHADERS; i++) {
		glAttachShader(m_program, m_shaders[i]);
	}

	glBindAttribLocation(m_program, 0, "position");

	glLinkProgram(m_program);

	glGetProgramiv(m_program, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(m_program, ERR_LOG, NULL, err_log);
		std::cout << "ERROR linking shader program:: " << m_program << " ::\n" << err_log << std::endl;
	}
}

GLuint Shader::compile_shader(const std::string& shader_src, GLenum shader_type) {
	GLuint shader;
	//We have to convert to a type that OpenGL understands
	const GLchar* src[1];
	GLint src_length[1];

	src[0] = shader_src.c_str();
	src_length[0] = shader_src.length();

	//Create the shader and compile it
	shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, src, src_length);
	glCompileShader(shader);

	//Check for compilation errors
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	//If compilation had errors
	if (!success) {
		glGetShaderInfoLog(shader, ERR_LOG, NULL, err_log);
		std::cout << "Error compiling shader::- " << shader << " -::\n" << err_log << std::endl;
	}

	return shader;
}

std::string Shader::load_shader(const std::string& filename){
	std::string line;
	std::ifstream shader_file(filename);
	std::string shader_src;

	if (shader_file.is_open()) {
		while (std::getline(shader_file, line)) {
			shader_src += line;
			shader_src.append("\n");
		}
		shader_file.close();
	}
	else {
		std::cout << "--Unable to load shader file--" << std::endl;
	}

	return shader_src;
}

Shader::~Shader()
{
	for (int i = 0; i < MAX_SHADERS; i++) {
		glDeleteShader(m_shaders[i]);
	}
}
