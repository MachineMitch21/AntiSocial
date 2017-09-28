#include "Window.h"

using antisocial::Window;

#include "stb_image.h"

bool Window::_keys[MAX_KEYS];
bool Window::_buttons[MAX_MOUSE_BUTTONS];
double Window::_x;
double Window::_y;


Window::Window(const std::string title, int width, int height)
	: 	_title(title),
		_width(width),
		_height(height)
{

	for (int i = 0; i < MAX_KEYS; i++) {
		_keys[i] = false;
	}

	for (int i = 0; i < MAX_MOUSE_BUTTONS; i++) {
		_buttons[i] = false;
	}

	if (!init())
		glfwTerminate();
}

bool Window::IsClosed() {
	return glfwWindowShouldClose(_window);
}

bool Window::isKeyPressed(unsigned int keycode) {

	if (keycode >= MAX_KEYS) {
		return false;
	}
	return _keys[keycode];
}

bool Window::isMouseButtonPressed(unsigned int button) {
	if (button >= MAX_MOUSE_BUTTONS) {
		return false;
	}
	return _buttons[button];
}

void Window::close() {
	glfwSetWindowShouldClose(_window, GL_TRUE);
}

double Window::getX() {
	return _x;
}

double Window::getY() {
	return _y;
}

int Window::getWidth() {
	return _width;
}

int Window::getHeight() {
	return _height;
}

void Window::setCursor(CURSOR_MODE mode) {
	if (mode == DISABLE) {
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		_cursorActive = false;
	}

	else if (mode == SHOW) {
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		_cursorActive = true;
	}
}

void Window::setIcon(const std::string path) {

#ifndef __APPLE__

	if (path != "") {
		int width, height, numComponents;
		
		GLFWimage icon[1];

		icon[0].pixels = stbi_load(path.c_str(), &width, &height, &numComponents, 4);

		if (icon[0].pixels == NULL) {
			std::cerr << "Failed to load icon image" << std::endl;
			return;
		}
		
		glfwSetWindowIcon(_window, 1, icon);

		stbi_image_free(icon[0].pixels);
			
	}
	else {
		glfwSetWindowIcon(_window, 0, NULL);
	}

#else
	std::cout << "Icon cannot be set on OS X" << std::endl;
#endif // __APPLE__
}

bool Window::isCursorActive() {
	return _cursorActive;
}

bool Window::isMinimized() {
	return _minimized;
}

void Window::enableVSYNC(bool enable) {
	glfwSwapInterval(enable);
}

void Window::update() {
	glfwPollEvents();
	glfwSwapBuffers(_window);
}

void Window::clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::init() {

	bool isInitialized = true;
	GLenum status;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glfwInit();

	std::cout << "Using GLFW VERSION: " << glfwGetVersionString() << std::endl;	

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//TODO: Setup fullscreen to non-fullscreen modes...
	//		For now the window will default to the width and height it was initialized with
	GLFWvidmode* mode;
	GLFWmonitor* primary;

	primary = glfwGetPrimaryMonitor();
	mode = (GLFWvidmode*)glfwGetVideoMode(primary);

	_window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);

	if (_window == nullptr) {
		std::cerr << "Failed to create GLFW window!" << std::endl;
		isInitialized = false;
	}

	glfwMakeContextCurrent(_window);
	glViewport(0, 0, _width, _height);

	glewExperimental = GL_TRUE;

	status = glewInit();

	if (status != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		isInitialized = false;
	}

	glfwGetFramebufferSize(_window, &_width, &_height);
	glfwSetWindowUserPointer(_window, this);

	glfwSetKeyCallback(_window, key_callback);
	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
	glfwSetCursorPosCallback(_window, cursor_position_callback);
	glfwSetMouseButtonCallback(_window, mouse_button_callback);
	glfwSetScrollCallback(_window, scroll_callback);
	glfwSetWindowIconifyCallback(_window, window_iconify_callback);
	glfwSetErrorCallback(error_callback);
	
	return isInitialized;
}

//Callback functions

void antisocial::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->_keys[key] = (action != GLFW_RELEASE);
}

void antisocial::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->_width = width;
	win->_height = height;
	glViewport(0, 0, width, height);
}

void antisocial::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->_x = xpos;
	win->_y = ypos;
}

void antisocial::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->_buttons[button] = (action != GLFW_RELEASE);
}

void antisocial::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
}

void antisocial::window_iconify_callback(GLFWwindow* window, int iconified) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);

	win->_minimized = iconified;
}

void antisocial::error_callback(int error, const char* description) {
	//TODO: Create a logging system that can log these errors for future reference
	std::cerr << "ERROR::(" << error << ")::\n" << description << std::endl;
}

