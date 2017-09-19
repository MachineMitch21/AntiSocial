
#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "vector3.h"

#define MAX_KEYS 1024
#define MAX_MOUSE_BUTTONS 32

class Window
{
public:
	Window(const std::string title, int width, int height);
	~Window();

	enum CURSOR_MODE{
		SHOW,
		DISABLE
	};

	bool IsClosed();
	void update();
	void clear(float r, float g, float b, float a);
	double getX();
	double getY();
	int getWidth();
	int getHeight();
	void setCursor(CURSOR_MODE mode);
	
	bool isKeyPressed(unsigned int keycode);
	bool isMouseButtonPressed(unsigned int button);
	bool isCursorActive();
	void close();

private:
	bool init();
	friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	
private:
	GLFWwindow* m_window;

	bool cursorActive;
	int m_height;
	int m_width;
	std::string m_title;
	static bool	m_keys[MAX_KEYS];
	static bool	m_buttons[MAX_MOUSE_BUTTONS];
	static double mx, my;

};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

#endif
