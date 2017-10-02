
#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

namespace antisocial {

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
		void setIcon(const std::string path);

		bool isCursorActive();
		bool isMinimized();
		void close();

		void enableVSYNC(bool enable);

	private:
		bool init();
		friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		friend void window_iconify_callback(GLFWwindow* window, int iconified);
		friend void error_callback(int error, const char* description);

	private:
		GLFWwindow* _window;

		std::string _title;
		int _height;
		int _width;
		static double _x, _y;
		bool _cursorActive;
		bool _minimized;

	};

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void window_iconify_callback(GLFWwindow* window, int iconified);
	void error_callback(int error, const char* description);

}



#endif
