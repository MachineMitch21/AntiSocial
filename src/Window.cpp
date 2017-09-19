#include "Window.h"

bool Window::m_keys[MAX_KEYS];
bool Window::m_buttons[MAX_MOUSE_BUTTONS];
double Window::mx;
double Window::my;


Window::Window(const std::string title, int width, int height)
{
	m_title = title;
	m_width = width;
	m_height = height;

	for (int i = 0; i < MAX_KEYS; i++) {
		m_keys[i] = false;
	}

	for (int i = 0; i < MAX_MOUSE_BUTTONS; i++) {
		m_buttons[i] = false;
	}

	if (!init())
		glfwTerminate();

	glewExperimental = GL_TRUE;
}

bool Window::IsClosed() {
	return glfwWindowShouldClose(m_window);
}

bool Window::isKeyPressed(unsigned int keycode) {

	if (keycode >= MAX_KEYS) {
		return false;
	}
	return m_keys[keycode];
}

bool Window::isMouseButtonPressed(unsigned int button) {
	if (button >= MAX_MOUSE_BUTTONS) {
		return false;
	}
	return m_buttons[button];
}

void Window::close() {
	glfwSetWindowShouldClose(m_window, GL_TRUE);
}

double Window::getX() {
	return mx;
}

double Window::getY() {
	return my;
}

int Window::getWidth() {
	return m_width;
}

int Window::getHeight() {
	return m_height;
}

void Window::setCursor(CURSOR_MODE mode) {
	if (mode == DISABLE) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		cursorActive = false;
	}

	else if (mode == SHOW) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		cursorActive = true;
	}
}

bool Window::isCursorActive() {
	return cursorActive;
}

void Window::update() {
	glfwPollEvents();
	glfwSwapBuffers(m_window);
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);

	if (m_window == nullptr) {
		std::cerr << "Failed to create GLFW window!" << std::endl;
		isInitialized = false;
	}

	glfwMakeContextCurrent(m_window);
	glViewport(0, 0, m_width, m_height);

	status = glewInit();

	if (status != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		isInitialized = false;
	}

	glfwGetFramebufferSize(m_window, &m_width, &m_height);
	glfwSetWindowUserPointer(m_window, this);

	glfwSetKeyCallback(m_window, key_callback);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	glfwSetCursorPosCallback(m_window, cursor_position_callback);
	glfwSetMouseButtonCallback(m_window, mouse_button_callback);
	glfwSetScrollCallback(m_window, scroll_callback);
	
	return isInitialized;
}

//Callback functions

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->m_keys[key] = (action != GLFW_RELEASE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->m_width = width;
	win->m_height = height;
	glViewport(0, 0, width, height);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->mx = xpos;
	win->my = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->m_buttons[button] = (action != GLFW_RELEASE);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
}

