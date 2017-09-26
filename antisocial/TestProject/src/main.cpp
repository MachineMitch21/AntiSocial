
#include <Window.h>
#include <Shader.h>
#include <matrix4.h>
#include <vector3.h>
#include <string>

using antisocial::Matrix4;
using antisocial::Vector3;

int main(int argc, char** argv)
{
	antisocial::Window w("USING ANTISOCIAL LIB", 800, 600);

	w.setIcon("../../extras/antisocial_icon.png");
	w.enableVSYNC(true);

	Matrix4 projection; 
	Matrix4 view = Matrix4::lookAt(Vector3(4,3,3), Vector3(0,0,0), Vector3(0,1,0));
	
	float vertices[]
	{
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	std::string srcs[2] = { "../../shaders/shader.vert", "../../shaders/shader.frag" };
	GLenum types[2] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };

	antisocial::Shader shader(srcs, types);
		
	GLuint vao, vbo;

	while(!w.IsClosed())
	{
		Matrix4 model(1.0f);
		model = Matrix4::translate(model, Vector3(0.25f, 0.25f, 0.0f));
		model = Matrix4::rotate(model, (float)glfwGetTime() * 10, Vector3(0.0f, 0.0f, 1.0f));
		
		shader.bind();

		GLuint transformLoc = glGetUniformLocation(shader.getProgram(), "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, model.toArray());
		
		if (w.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			exit(0);
		}

		w.clear(.25f, .5f, .75f, 1.0f);
	
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
	
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

		glDrawArrays(GL_TRIANGLES, 0, 3); 
		glBindVertexArray(0);


		w.update();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	return 0;
}
