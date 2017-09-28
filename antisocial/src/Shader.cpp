#include <Shader.h>

using antisocial::Shader;

Shader::Shader(std::string* files, GLenum* types)
{
	_handle = glCreateProgram();

	for (int i = 0; i < MAX_SHADERS; i++) {
		_shaders[i] = compile_shader(load_shader(files[i]), types[i]);
	}

	link_program();
}

void Shader::bind() {
	glActiveTexture(GL_TEXTURE0);
	glUseProgram(_handle);
}

void Shader::setMatrix4(const std::string& name, const float* v)
{
	GLuint uniformLocation = glGetUniformLocation(_handle, name.c_str());
	glUniformMatrix4fv(uniformLocation, 1, GL_TRUE, v);
}

void Shader::setVector2(const std::string& name, float v1, float v2)
{
	GLuint uniformLocation = glGetUniformLocation(_handle, name.c_str());
	glUniform2f(uniformLocation, v1, v2);
}

void Shader::setVector3(const std::string& name, float v1, float v2, float v3)
{
	GLuint uniformLocation = glGetUniformLocation(_handle, name.c_str());
	glUniform3f(uniformLocation, v1, v2, v3);
}

void Shader::setVector4(const std::string& name, float v1, float v2, float v3, float v4)
{
	GLuint uniformLocation = glGetUniformLocation(_handle, name.c_str());
	glUniform4f(uniformLocation, v1, v2, v3, v4);
}

void Shader::setFloat(const std::string& name, float v)
{
	GLuint uniformLocation = glGetUniformLocation(_handle, name.c_str());
	glUniform1f(uniformLocation, v);
}

void Shader::setBool(const std::string& name, bool v)
{
	GLuint uniformLocation = glGetUniformLocation(_handle, name.c_str());
	glUniform1i(uniformLocation, v);
}

void Shader::setInteger(const std::string& name, int v)
{
	GLuint uniformLocation = glGetUniformLocation(_handle, name.c_str());
	glUniform1i(uniformLocation, v);
}

void Shader::setUInteger(const std::string& name, unsigned int v)
{
	GLuint uniformLocation = glGetUniformLocation(_handle, name.c_str());
	glUniform1ui(uniformLocation, v);
}

GLuint& Shader::getProgram() {
	return _handle;
}

void Shader::link_program() {

	//Attach shaders to newly create program and then link everything
	for (int i = 0; i < MAX_SHADERS; i++) {
		glAttachShader(_handle, _shaders[i]);
	}

	glBindAttribLocation(_handle, 0, "Pos");
	glBindAttribLocation(_handle, 1, "Color");
	glBindAttribLocation(_handle, 2, "TexCoord");

	glLinkProgram(_handle);

	glGetProgramiv(_handle, GL_LINK_STATUS, &_success);

	if (!_success) {
		glGetProgramInfoLog(_handle, ERR_LOG, NULL, _errLog);
		std::cout << "ERROR linking shader program:: " << _handle << " ::\n" << _errLog << std::endl;
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
	glGetShaderiv(shader, GL_COMPILE_STATUS, &_success);

	//If compilation had errors
	if (!_success) {
		glGetShaderInfoLog(shader, ERR_LOG, NULL, _errLog);
		std::cout << "Error compiling shader::- " << shader << " -::\n" << _errLog << std::endl;
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
		glDeleteShader(_shaders[i]);
	}
}
