
#include <Window.h>

int main(int argc, char** argv)
{
	Window w("USING ANTISOCIAL LIB", 800, 600);

	float vertices[]
	{
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	while(!w.IsClosed())
	{
		w.clear(.25f, .5f, .75f, 1.0f);
		
		GLuint vao, vbo;

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
	return 0;
}
