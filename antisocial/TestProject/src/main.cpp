
#include <AntiSocial.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#define _USEORTHO_

using antisocial::Matrix4;
using antisocial::Vector3;
using antisocial::Texture2D;
using antisocial::Mesh;
using namespace antisocial::input;

bool drawWireframe = false;

void printFPSandMilliSeconds(int& nbFrames, float& lastTimeCount, float& currentFrame);
void debug_glm_mat4(glm::mat4& matToDebug);

int main(int argc, char** argv)
{
	antisocial::Window w("USING ANTISOCIAL LIB", 800, 600);
	Input i;

	Texture2D texture("../../extras/bricks.jpg");
	Texture2D overridingTexture("../../extras/bricks.jpg");

	w.setIcon("../../extras/antisocial_icon.png");
	w.enableVSYNC(true);

	float vertices[]
	{
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,

        -0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f
	};

	unsigned int indices[]
	{
		0,1,3,  0,3,2,
		1,4,7,	1,7,3,
		4,5,6,	4,6,7,
		5,0,2,	5,2,6,
		4,1,0,	4,0,5,
		2,3,7,	2,3,6
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

	GLuint vao, vbo, ibo;

	int iboSize;

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &iboSize);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	float 	currentFrame = 0.0f,
			deltaTime = 0.0f,
			lastFrame = 0.0f;

	float texChangeTimer = 0.0f;
	int texChoice = 0;

	float lastTimeCount = glfwGetTime();
	int nbFrames = 0;

	glm::mat4 view;
	glm::mat4 projection;

#ifdef _USEORTHO_
	projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, 1.0f, -1.0f);
#else
	projection = glm::perspective(glm::radians(45.0f), (float)w.getWidth() / (float)w.getHeight(), 0.1f, 1000.0f);
#endif

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));

	shader.bind();

	shader.setMatrix4("view", /*view._elements*/glm::value_ptr(view));
	shader.setMatrix4("projection", /*projection._elements*/glm::value_ptr(projection));
	shader.setVector3("ambientLightColor", 0.15f, 0.15f, 0.15f);
	shader.setVector3("lightColor", 1.0f, 1.0f, 1.0f);

	float verticeOffset = 0.0f;

	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 5.0f);

	// GAME LOOP
	while(!w.IsClosed())
	{
		w.clear(0.1f, 0.1f, 0.1f, 1.0f);

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if (Input::keyPressed(KeyCode::U))
		{
			verticeOffset += .01f;
			if (verticeOffset > 1.0f)
			{
				verticeOffset = 1.0f;
			}
		}

		if (Input::keyPressed(KeyCode::J))
		{
			verticeOffset -= .01f;
			if (verticeOffset < 0.0f)
			{
				verticeOffset = 0.0f;
			}
		}

		if (Input::keyDown(KeyCode::ESCAPE))
		{
			break;
		}

		if (Input::keyPressed(KeyCode::W))
		{
			lightPos.z -= deltaTime * 5.0f;
		}
		else if (Input::keyPressed(KeyCode::S))
		{
			lightPos.z += deltaTime * 5.0f;
		}

		if (Input::keyPressed(KeyCode::A))
		{
			lightPos.x -= deltaTime * 5.0f;
		}
		else if (Input::keyPressed(KeyCode::D))
		{
			lightPos.x += deltaTime * 5.0f;
		}

		if (Input::keyPressed(KeyCode::Q))
		{
			lightPos.y += deltaTime * 5.0f;
		}
		else if (Input::keyPressed(KeyCode::E))
		{
			lightPos.y -= deltaTime * 5.0f;
		}

		shader.setFloat("verticeOffset", verticeOffset);
		shader.setFloat("time", currentFrame);
		shader.setVector3("lightPos", lightPos.x, lightPos.y, lightPos.z);

		nbFrames++;
		printFPSandMilliSeconds(nbFrames, lastTimeCount, currentFrame);

		// DONT CHANGE TEXTURES RIGHT NOW
		// texChangeTimer += deltaTime;
		//
		// if (texChangeTimer >= 1.0f)
		// {
		// 	std::string texStr;
		// 
		// 	texChangeTimer = 0.0f;
		// 	if (texChoice > 3) texChoice = 0;
		//
		// 	switch (texChoice) {
		// 		case 0:
		// 			texStr = "../../extras/jim-carrey.png";
		// 			break;
		// 		case 1:
		// 			texStr = "../../extras/index.png";
		// 			break;
		// 		case 2:
		// 			texStr = "../../extras/troll.png";
		// 			break;
		// 		case 3:
		// 			texStr = "../../extras/antisocial_icon.png";
		// 			break;
		// 	}
		//
		// 	texChoice++;
		//
		// 	texture.setImage(texStr);
		// }


		float zPos = 0.0f;
		int zCounter = 0;

		for (int i = 0; i < 10; i++)
		{
			positions[zCounter].z = zPos;
			glm::mat4 model;
			model = glm::translate(model, positions[zCounter]);
			//model = glm::rotate(model, currentFrame * 2.0f, glm::vec3(0, 1.0f, 0.0f));

			shader.setMatrix4("model", /*model._elements*/glm::value_ptr(model));

			if (zCounter < 5)
				texture.bind(0);
			else
				overridingTexture.bind(0);

			Mesh mesh(vertices, 36);
			mesh.setVBO(&vbo);
			mesh.setVAO(&vao);
			mesh.draw(false);
			//glDrawArrays(GL_TRIANGLES, 0, 36);
			//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			//shader.unbind();
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
	glDeleteBuffers(1, &ibo);

	return 0;
}


void printFPSandMilliSeconds(int& nbFrames, float& lastTimeCount, float& currentFrame)
{
	if (currentFrame - lastTimeCount >= 1.0f)
	{
		std::cout << "Milliseconds: " << 1000.0f / nbFrames << std::endl;
		std::cout << "Frames Per Second: " << nbFrames << std::endl;

		nbFrames = 0;
		lastTimeCount += 1.0f;
	}
}


void debug_glm_mat4(glm::mat4& matToDebug)
{
	std::cout << "----------Printing Matrix4 elements----------" << std::endl;
	float arr[16] = {0.0f};

	const float* matVals = (const float*)glm::value_ptr(matToDebug);
	for (int i = 0; i < 16; i++)
	{
		arr[i] = matVals[i];
		std::cout << arr[i] << ", ";

		if (i == 3 || i == 7 || i == 11 || i == 15)
			std::cout << std::endl;
	}

	std::cout << "---------------------------------------------" << std::endl;
}
