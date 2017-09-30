
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
	Texture2D overridingTexture("../../extras/bricks.jpg");

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

	glm::vec3 positions[10]
	{
		glm::vec3(-2.5f,-2.0f, 0.0f),
		glm::vec3(-1.0f,-2.0f, 0.0f),
		glm::vec3( 1.0f,-2.0f, 0.0f),
		glm::vec3( 2.5f,-2.0f, 0.0f),
		glm::vec3(-1.5f,-1.0f, 0.0f),
		glm::vec3( 0.0f,-1.0f, 0.0f),
		glm::vec3( 1.5f,-1.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3( 1.0f, 0.0f, 0.0f),
		glm::vec3( 0.0f, 1.0f, 0.0f)
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

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	float 	currentFrame = 0.0f,
			deltaTime = 0.0f,
			lastFrame = 0.0f;

	float texChangeTimer = 0.0f;
	int texChoice = 0;

	float lastTimeCount = glfwGetTime();
	int nbFrames = 0;

	glm::mat4 view;
	glm::mat4 projection;

	projection = glm::perspective(glm::radians(45.0f), (float)w.getWidth() / (float)w.getHeight(), 0.1f, 1000.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));

	shader.bind();

	shader.setMatrix4("view", /*view._elements*/glm::value_ptr(view));
	shader.setMatrix4("projection", /*projection._elements*/glm::value_ptr(projection));

	while(!w.IsClosed())
	{
		if (w.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			break;
		}

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		nbFrames++;
		if (currentFrame - lastTimeCount >= 1.0f)
		{
			std::cout << "Milliseconds: " << 1000.0f / nbFrames << std::endl;
			std::cout << "Frames Per Second: " << nbFrames << std::endl;

			nbFrames = 0;
			lastTimeCount += 1.0f;
		}

		texChangeTimer += deltaTime;

		if (texChangeTimer >= 1.0f)
		{
			std::string texStr;

			texChangeTimer = 0.0f;
			if (texChoice > 3) texChoice = 0;

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


		w.clear(.25f, .5f, .75f, 1.0f);

  		// Matrix4 view;
		// Matrix4 projection;
		// Matrix4 model;
		//
		// projection = Matrix4::perspective(antisocial::radians(45.0f), (float)w.getWidth() / (float)w.getHeight(), 0.1f, 100.0f);
		//
		// view = Matrix4::translate(view, Vector3(0.0f, 0.0f, 0.0f));
		//
		// model = Matrix4::translate(model, Vector3(0.0f, 0.0f, -5.0f));
		// model = Matrix4::rotate(model, antisocial::radians((float)glfwGetTime() * 5), Vector3(0.0f, 1.0f, 1.0f));

//		std::cout << "--Printing Matrix4--" << std::endl;
//		proj.toString();


		//DEBUG CODE FOR GLM::MAT4
		// float arr[16] = {0.0f};
		//
		// const float* matVals = (const float*)glm::value_ptr(projection);
		// for (int i = 0; i < 16; i++)
		// {
		// 	arr[i] = matVals[i];
		// 	std::cout << arr[i] << ", ";
		//
		// 	if (i == 3 || i == 7 || i == 11 || i == 15)
		// 		std::cout << std::endl;
		// }

		float zPos = 0.0f;
		int zCounter = 0;

		for (int i = 0; i < 10000; i++)
		{
			positions[zCounter].z = zPos;
			glm::mat4 model;
			model = glm::translate(model, positions[zCounter]);
			model = glm::rotate(model, currentFrame * 2.0f, glm::vec3(0, 1.0f, 1.0f));

			shader.setMatrix4("model", /*model._elements*/glm::value_ptr(model));

			if (zCounter < 5)
				texture.bind(0);
			else
				overridingTexture.bind(0);

			glDrawArrays(GL_TRIANGLES, 0, 36);

			zCounter++;
			if (zCounter > 9)
			{
				zCounter = 0;
				zPos -= 5.0f;
			}
		}

		w.update();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	return 0;
}
