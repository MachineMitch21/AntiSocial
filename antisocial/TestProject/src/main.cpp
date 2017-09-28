
#include <Window.h>
#include <Shader.h>
#include <matrix4.h>
#include <vector3.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using antisocial::Matrix4;
using antisocial::Vector3;

int main(int argc, char** argv)
{
	antisocial::Window w("USING ANTISOCIAL LIB", 800, 600);

	w.setIcon("../../extras/antisocial_icon.png");
	w.enableVSYNC(true);

	float vertices[]
	{
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.0f
	};

	std::string srcs[2] = { "../../shaders/shader.vert", "../../shaders/shader.frag" };
	GLenum types[2] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };

	antisocial::Shader shader(srcs, types);

	GLuint vao, vbo;

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	while(!w.IsClosed())
	{
		if (w.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			exit(0);
		}

		w.clear(.25f, .5f, .75f, 1.0f);

//		Matrix4 view;
//		Matrix4 projection;
//		Matrix4 model;
//
//		projection = Matrix4::perspective(antisocial::radians(45.0f), (float)w.getWidth() / (float)w.getHeight(), 0.1f, 100.0f);
//
//		view = Matrix4::translate(view, Vector3(0.0f, 0.0f, 0.0f));

//		model = Matrix4::translate(model, Vector3(0.0f, 0.0f, -5.0f));
//		model = Matrix4::rotate(model, antisocial::radians((float)glfwGetTime() * 5), Vector3(0.0f, 1.0f, 1.0f));

		shader.bind();

		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 model;

		projection = glm::perspective(glm::radians(45.0f), (float)w.getWidth() / (float)w.getHeight(), 0.1f, 100.0f);

		view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
		model = glm::rotate(model, glm::radians((float)glfwGetTime() * 25), glm::vec3(0.0f, 1.0f, 1.0f));

		GLuint modelLoc = glGetUniformLocation(shader.getProgram(), "model");
		GLuint viewLoc = glGetUniformLocation(shader.getProgram(), "view");
		GLuint projLoc = glGetUniformLocation(shader.getProgram(), "projection");

//		glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection._elements);
//		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model._elements);
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view._elements);

		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		w.update();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	return 0;
}
