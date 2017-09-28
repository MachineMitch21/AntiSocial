
#include <Window.h>
#include <Shader.h>
#include <Matrix4.h>
#include <Vector3.h>
#include <Texture2D.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using antisocial::Matrix4;
using antisocial::Vector3;
using antisocial::Texture2D;

int main(int argc, char** argv)
{
	antisocial::Window w("USING ANTISOCIAL LIB", 800, 600);

	Texture2D texture("../../extras/bricks.jpg");

	w.setIcon("../../extras/antisocial_icon.png");
	w.enableVSYNC(true);

	float vertices[]
	{
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	shader.bind();
	shader.setInteger("tex", 0);

	float 	currentFrame = 0.0f,
			deltaTime = 0.0f,
			lastFrame = 0.0f;

	float texChangeTimer = 0.0f;
	int texChoice = 0;

	while(!w.IsClosed())
	{
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		texChangeTimer += deltaTime;

		if (texChangeTimer >= 1.0f)
		{
			std::string texStr;

			texChangeTimer = 0.0f;
			if (texChoice > 3) texChoice = 0;

			std::cout << texChoice << std::endl;

			switch (texChoice) {
				case 0:
					texStr = "../../extras/jim-carrey.png";
					break;
				case 1:
					texStr = "../../extras/index.png";
					break;
				case 2:
					texStr = "../../extras/troll.png";
					break;
				case 3:
					texStr = "../../extras/antisocial_icon.png";
					break;
			}

			texChoice++;

			texture.setImage(texStr);
		}

		if (w.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			exit(0);
		}

		w.clear(.25f, .5f, .75f, 1.0f);
/*
   		Matrix4 view;
		Matrix4 projection;
		Matrix4 model;

		projection = Matrix4::perspective(antisocial::radians(45.0f), (float)w.getWidth() / (float)w.getHeight(), 0.1f, 100.0f);

		view = Matrix4::translate(view, Vector3(0.0f, 0.0f, 0.0f));

		model = Matrix4::translate(model, Vector3(0.0f, 0.0f, -5.0f));
		model = Matrix4::rotate(model, antisocial::radians((float)glfwGetTime() * 5), Vector3(0.0f, 1.0f, 1.0f));
*/
//		std::cout << "--Printing Matrix4--" << std::endl;
//		proj.toString();

		texture.bind(0);
		shader.bind();


		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 model;

		projection = glm::perspective(glm::radians(45.0f), (float)w.getWidth() / (float)w.getHeight(), 0.1f, 100.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
		model = glm::rotate(model, glm::radians((float)glfwGetTime() * 25), glm::vec3(0.0f, 1.0f, 1.0f));

		//DEBUG CODE FOR GLM::MAT4
		/*
		float arr[16] = {0.0f};

		const float* matVals = (const float*)glm::value_ptr(projection);
		for (int i = 0; i < 16; i++)
		{
			arr[i] = matVals[i];
			std::cout << arr[i] << ", ";

			if (i == 3 || i == 7 || i == 11 || i == 15)
				std::cout << std::endl;
		}
		*/


		shader.setMatrix4("model", /*model._elements*/glm::value_ptr(model));
		shader.setMatrix4("view", /*view._elements*/glm::value_ptr(view));
		shader.setMatrix4("projection", /*projection._elements*/glm::value_ptr(projection));

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		w.update();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	return 0;
}
