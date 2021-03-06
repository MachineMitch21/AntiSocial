#include <AntiSocial.h>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>

using antisocial::Matrix4;
using antisocial::Vector3;
using antisocial::Texture2D;
using antisocial::Mesh;
using antisocial::Shader;
using antisocial::Camera;
using antisocial::Skybox;
using antisocial::MOVEMENT_DIRECTION;

using namespace antisocial::input;

bool drawWireframe = false;

void prepCubeObjectData(GLuint* vao, GLuint* vbo, std::vector<float> vertices);
void prepLightObjectData(GLuint* vao, GLuint* vbo, std::vector<float> vertices);
void prepSkyboxObjectData(GLuint* vao, GLuint* vbo, std::vector<float> vertices);

void printFPSandMilliSeconds(int& nbFrames, float& lastTimeCount, float& currentFrame);
void debug_glm_mat4(glm::mat4& matToDebug);

int main(int argc, char** argv)
{
	antisocial::Window w("ANTISOCIAL TEST PROJECT", 800, 600);
	Input i;

	Camera camera(45.0f, 0.0f, 0.0f, 10.0f, (float)w.getWidth() / (float)w.getHeight(), 0.1f, 1000.0f);

	Texture2D texture("../../extras/bricks.jpg");
	Texture2D overridingTexture("../../extras/bricks.jpg");

	w.setIcon("../../extras/antisocial_icon.png");
	w.enableVSYNC(true);

	std::vector<float> skyboxVertices =
	{
		-1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
	};

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

	Shader shader("../../shaders/shader.vert", "../../shaders/shader.frag");
	Shader lightShader("../../shaders/lightObj.vert", "../../shaders/lightObj.frag");
	Shader skyboxShader("../../shaders/skybox.vert", "../../shaders/skybox.frag");

	GLuint vao, vbo, lightVao, lightVbo, skyboxVao, skyboxVbo;

	prepCubeObjectData(&vao, &vbo, vertices);
	prepLightObjectData(&lightVao, &lightVbo, lightVertices);
	prepSkyboxObjectData(&skyboxVao, &skyboxVbo, skyboxVertices);

	Mesh* skyboxMesh = new Mesh(36);
	skyboxMesh->setVAO(&skyboxVao);
	skyboxMesh->setVBO(&skyboxVbo);

	std::string orbitalElement = "../../extras/skybox/orbital-element/orbital-element";
	std::string cloudtop = "../../extras/skybox/cloudtop/cloudtop";

	Skybox skybox(	orbitalElement + "_ft.tga",
					orbitalElement + "_bk.tga",
					orbitalElement + "_up.tga",
					orbitalElement + "_dn.tga",
					orbitalElement + "_rt.tga",
					orbitalElement + "_lf.tga",
					skyboxMesh);

	float 	currentFrame = 0.0f,
			deltaTime = 0.0f,
			lastFrame = 0.0f;

	float lastTimeCount = glfwGetTime();

	int nbFrames = 0;

	glm::mat4 view;
	glm::mat4 projection;
	projection = glm::perspective(camera.getFOV(), camera.getAspectRatio(), camera.getNearClip(), camera.getFarClip());

	shader.bind();
	shader.setMatrix4("projection", /*projection._elements*/glm::value_ptr(projection));
	shader.setVector3("ambientLightColor", 0.1f, 0.1f, 0.1f);
	shader.setVector3("lightColor", 1.0f, 1.0f, 1.0f);
	shader.setInteger("tex", 0);
	shader.unbind();

	lightShader.bind();
	lightShader.setMatrix4("projection", glm::value_ptr(projection));
	lightShader.unbind();

	skyboxShader.bind();
	skyboxShader.setMatrix4("projection", glm::value_ptr(projection));
	skyboxShader.unbind();

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

		float xOffset = 0.0f;
		float yOffset = 0.0f;

 	#ifdef __VIRTUAL_BOX__
		if (Input::mouseButtonPressed(MouseButton::M_RIGHT))
		{
			xOffset = Input::getCurrentCursorPos().x - oldMousePos.x;
			yOffset = oldMousePos.y - Input::getCurrentCursorPos().y;
		}
	#else
		xOffset = Input::getCurrentCursorPos().x - oldMousePos.x;
		yOffset = oldMousePos.y - Input::getCurrentCursorPos().y;
	#endif
		oldMousePos = Input::getCurrentCursorPos();

		glm::vec3 camDirection;
		float camSpeedMultiplier = 1.0f;

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

		if (Input::keyPressed(KeyCode::W))
		{
			camDirection += camera.getFront();
		}

		if (Input::keyPressed(KeyCode::S))
		{
			camDirection += -camera.getFront();
		}

		if (Input::keyPressed(KeyCode::A))
		{
			camDirection += -glm::normalize(glm::cross(camera.getFront(), camera.getUp()));
		}

		if (Input::keyPressed(KeyCode::D))
		{
			camDirection += glm::normalize(glm::cross(camera.getFront(), camera.getUp()));
		}

		if (Input::keyPressed(KeyCode::LEFT_SHIFT) || Input::keyPressed(KeyCode::RIGHT_SHIFT))
		{
			camSpeedMultiplier = 2.5f;
		}

		if (Input::keyPressed(KeyCode::LEFT_CTRL))
		{
			camSpeedMultiplier = 0.5f;
		}

		if (Input::keyDown(KeyCode::V))
		{
			drawWireframe = !drawWireframe;
		}

		camera.move(camDirection, camSpeedMultiplier, xOffset, yOffset, deltaTime, true);
		view = camera.getViewMatrix();

		glm::mat4 skyboxModel;
		skyboxModel = glm::translate(skyboxModel, camera.getPosition());

		skyboxShader.bind();
		skyboxShader.setFloat("time", currentFrame);
		skyboxShader.setMatrix4("view", glm::value_ptr(view));
		skyboxShader.setMatrix4("model", glm::value_ptr(skyboxModel));
		skyboxShader.setInteger("cubeTex", 0);
		skybox.draw();
		skyboxShader.unbind();

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
			model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

			lightShader.setMatrix4("model", glm::value_ptr(model));
			Mesh lightMesh(36);
			lightMesh.setVBO(&lightVbo);
			lightMesh.setVAO(&lightVao);
			lightMesh.draw(false);
		}
		lightShader.unbind();

		w.update();

		nbFrames++;
		//printFPSandMilliSeconds(nbFrames, lastTimeCount, currentFrame);
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

void prepSkyboxObjectData(GLuint* vao, GLuint* vbo, std::vector<float> vertices)
{
	glGenBuffers(1, vbo);
	glGenVertexArrays(1, vao);

	glBindVertexArray(*vao);

	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
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
