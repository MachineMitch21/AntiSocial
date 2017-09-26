
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
	
	float vertices[]
	{
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f, 
        -0.5f,  0.5f, -0.5f,  
        -0.5f, -0.5f, -0.5f,  

        -0.5f, -0.5f,  0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f,  

        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f,  
        -0.5f, -0.5f, -0.5f,  
        -0.5f, -0.5f, -0.5f,  
        -0.5f, -0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f,  

         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f, 
         0.5f,  0.5f,  0.5f,  

        -0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f, -0.5f,  

        -0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f, -0.5f  
	};

	std::string srcs[2] = { "../../shaders/shader.vert", "../../shaders/shader.frag" };
	GLenum types[2] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };

	antisocial::Shader shader(srcs, types);
		
	GLuint vao, vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while(!w.IsClosed())
	{
		w.clear(.25f, .5f, .75f, 1.0f);

		Matrix4 model;
		Matrix4 view;
		Matrix4 projection;
		
		projection = Matrix4::perspective(antisocial::radians(45.0f), (float)w.getWidth() / (float)w.getHeight(), 0.1f, 100.0f);
				
		view = Matrix4::translate(view, Vector3(0.0f, 0.0f, -3.0f));
		view = Matrix4::rotate(view, antisocial::radians((float)glfwGetTime() * 10), Vector3(0.0f, 1.0f, 0.0f));

		model = Matrix4::translate(model, Vector3(1.0f, 1.0f, -10.0f));
		//model = Matrix4::rotate(model, antisocial::radians((float)glfwGetTime()), Vector3(0.0f, 0.0f, 0.0f));
		
		shader.bind();

		GLuint modelLoc = glGetUniformLocation(shader.getProgram(), "model");
		GLuint viewLoc = glGetUniformLocation(shader.getProgram(), "view");
		GLuint projLoc = glGetUniformLocation(shader.getProgram(), "projection");
		
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, (GLfloat*)projection._elements);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat*)model._elements);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (GLfloat*)view._elements);
		
		if (w.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			exit(0);
		}

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 36); 
		glBindVertexArray(0);


		w.update();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	return 0;
}
