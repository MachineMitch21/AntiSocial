
#include <Window.h>
#include <Shader.h>
#include <string>

int main(int argc, char** argv)
{
	Window w("USING ANTISOCIAL LIB", 800, 600);

	w.setIcon("../../extras/antisocial_icon.png");

	float vertices[]
	{
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	std::string srcs[2] = { "../../shaders/shader.vert", "../../shaders/shader.frag" };
	GLenum types[2] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };

	Shader shader(srcs, types);
		
	GLuint vao, vbo;

	while(!w.IsClosed())
	{
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

		shader.bind();
		
		w.update();	
	}

	return 0;
}
