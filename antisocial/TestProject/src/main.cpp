
#include <AntiSocial.h>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>

//#define _USEORTHO_

using antisocial::Matrix4;
using antisocial::Vector3;
using antisocial::Texture2D;
using antisocial::Mesh;
using antisocial::Shader;
using antisocial::Camera;
using antisocial::MOVEMENT_DIRECTION;

using namespace antisocial::input;

bool drawWireframe = false;

void prepCubeObjectData(GLuint* vao, GLuint* vbo, std::vector<float> vertices);
void prepLightObjectData(GLuint* vao, GLuint* vbo, std::vector<float> vertices);

void printFPSandMilliSeconds(int& nbFrames, float& lastTimeCount, float& currentFrame);
void debug_glm_mat4(glm::mat4& matToDebug);

int main(int argc, char** argv)
{
	antisocial::Window w("ANTISOCIAL TEST PROJECT", 800, 600);
	Input i;

	w.setCursor(false);

	Camera camera(45.0f, 0.0f, 0.0f, 10.0f, (float)w.getWidth() / (float)w.getHeight(), 0.1f, 1000.0f);

	Texture2D texture("../../extras/bricks.jpg");
	Texture2D overridingTexture("../../extras/bricks.jpg");

	w.setIcon("../../extras/antisocial_icon.png");
	w.enableVSYNC(true);

	std::vector<float> vertices =
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

	std::vector<float> lightVertices =
	{
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
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

	Shader shader;

	shader.setVertexShader("../../shaders/shader.vert");
	shader.setFragmentShader("../../shaders/shader.frag");

	if (shader.link_program())
	{
		std::cout << "Cubes shader program was linked successfully" << std::endl;
	}
	else
	{
		std::cout << "Cubes shader program was not linked successfully" << std::endl;
	}

	Shader lightShader;

	lightShader.setVertexShader("../../shaders/lightObj.vert");
	lightShader.setFragmentShader("../../shaders/lightObj.frag");

	if (lightShader.link_program())
	{
		std::cout << "Lights shader program was linked successfully" << std::endl;
	}
	else
	{
		std::cout << "Lights shader program was not linked successfully" << std::endl;
	}

	GLuint vao, vbo;

	GLuint lightVao, lightVbo;

	prepCubeObjectData(&vao, &vbo, vertices);
	prepLightObjectData(&lightVao, &lightVbo, lightVertices);

	float 	currentFrame = 0.0f,
			deltaTime = 0.0f,
			lastFrame = 0.0f;

	float lastTimeCount = glfwGetTime();
	int nbFrames = 0;

	glm::mat4 view;
	glm::mat4 projection;

	#ifdef _USEORTHO_
		projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 1000.0f);
	#else
		projection = glm::perspective(camera.getFOV(), camera.getAspectRatio(), camera.getNearClip(), camera.getFarClip());
	#endif

	shader.bind();

	shader.setMatrix4("projection", /*projection._elements*/glm::value_ptr(projection));
	shader.setVector3("ambientLightColor", 0.1f, 0.1f, 0.1f);
	shader.setVector3("lightColor", 1.0f, 1.0f, 1.0f);
	shader.setInteger("tex", 0);

	shader.unbind();

	lightShader.bind();

	lightShader.setMatrix4("projection", glm::value_ptr(projection));

	lightShader.unbind();

	float verticeOffset = 0.0f;

	glm::vec3 lightPos = glm::vec3(0.0f, 2.5f, 5.0f);

	glm::vec2 oldMousePos = Input::getCurrentCursorPos();

	// GAME LOOP
	while(!w.IsClosed())
	{
		w.clear(0.1f, 0.1f, 0.1f, 1.0f);

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if (Input::keyDown(KeyCode::ESCAPE))
		{
			break;
		}

		if (Input::keyDown(KeyCode::C))
		{
			w.setCursor(!w.isCursorActive());
		}

		if (Input::keyPressed(KeyCode::UP))
		{
			verticeOffset += .01f;
			if (verticeOffset > 1.0f)
			{
				verticeOffset = 1.0f;
			}
		}

		if (Input::keyPressed(KeyCode::DOWN))
		{
			verticeOffset -= .01f;
			if (verticeOffset < 0.0f)
			{
				verticeOffset = 0.0f;
			}
		}

		float xOffset = Input::getCurrentCursorPos().x - oldMousePos.x;
		float yOffset = oldMousePos.y - Input::getCurrentCursorPos().y;

		oldMousePos = Input::getCurrentCursorPos();

		glm::vec3 camDirection;

		if (Input::keyPressed(KeyCode::W))
		{
			camDirection += camera.getFront();
		}
		else if (Input::keyPressed(KeyCode::S))
		{
			camDirection += -camera.getFront();
		}

		if (Input::keyPressed(KeyCode::A))
		{
			camDirection += -glm::normalize(glm::cross(camera.getFront(), camera.getUp()));
		}
		else if (Input::keyPressed(KeyCode::D))
		{
			camDirection += glm::normalize(glm::cross(camera.getFront(), camera.getUp()));
		}

		camera.move(camDirection, xOffset, yOffset, deltaTime, true);
		view = camera.getViewMatrix();


		if (Input::keyDown(KeyCode::V))
		{
			drawWireframe = !drawWireframe;
		}

		nbFrames++;
		printFPSandMilliSeconds(nbFrames, lastTimeCount, currentFrame);


		shader.bind();

		shader.setMatrix4("view", /*view._elements*/glm::value_ptr(view));
		shader.setFloat("verticeOffset", verticeOffset);
		shader.setFloat("time", currentFrame);
		shader.setVector3("lightPos", lightPos.x, lightPos.y, lightPos.z);
		shader.setFloat("ambientIntensity", .25f);
		shader.setFloat("specularStrength", .25f);

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, positions[i]);
			//model = glm::rotate(model, currentFrame, glm::vec3(0.0f, 1.0f, 1.0f));

			shader.setMatrix4("model", /*model._elements*/glm::value_ptr(model));

			texture.bind(0);

			Mesh mesh(36);
			mesh.setVBO(&vbo);
			mesh.setVAO(&vao);
			mesh.draw(drawWireframe);
		}

		shader.unbind();

		lightShader.bind();

		lightShader.setMatrix4("view", glm::value_ptr(view));
		lightShader.setFloat("time", currentFrame);

		for (int i = 0; i < 1; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, lightPos);

			lightShader.setMatrix4("model", glm::value_ptr(model));
			Mesh lightMesh(36);
			lightMesh.setVBO(&lightVbo);
			lightMesh.setVAO(&lightVao);
			lightMesh.draw(false);
		}

		lightShader.unbind();

		w.update();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	return 0;
}


void prepCubeObjectData(GLuint* vao, GLuint* vbo, std::vector<float> vertices)
{
	glGenBuffers(1, vbo);
	glGenVertexArrays(1, vao);

	glBindVertexArray(*vao);

	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));

}

void prepLightObjectData(GLuint* vao, GLuint* vbo, std::vector<float> vertices)
{
	glGenBuffers(1, vbo);
	glGenVertexArrays(1, vao);

	glBindVertexArray(*vao);

	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
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
