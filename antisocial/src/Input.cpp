
#include <Input.h>

using namespace antisocial::input;

bool Input::_keys[MAX_KEYS];
bool Input::_buttons[MAX_MOUSE_BUTTONS];
bool Input::_keysPrevious[MAX_KEYS];
bool Input::_buttonsPrevious[MAX_MOUSE_BUTTONS];

Input::Input()
{
    glfwSetKeyCallback(glfwGetCurrentContext(), key_callback);
    glfwSetMouseButtonCallback(glfwGetCurrentContext(), mouse_button_callback);
}

Input::~Input()
{

}

int Input::getState(KeyCode key)
{
    return (glfwGetKey(glfwGetCurrentContext(), key));
}

int Input::getState(MouseButton button)
{
    return (glfwGetMouseButton(glfwGetCurrentContext(), button));
}

bool Input::keyDown(KeyCode key)
{
    bool keyDownThisFrame = false;

    if (_keysPrevious[key] == true)
    {
        keyDownThisFrame = false;
    }
    else if (_keysPrevious[key] == false && _keys[key] == true)
    {
        keyDownThisFrame = true;
    }
    else if (_keysPrevious[key] == false && _keys[key] == false)
    {
        keyDownThisFrame = false;
    }

    _keysPrevious[key] = _keys[key];

    return keyDownThisFrame;
}

bool Input::keyPressed(KeyCode key)
{
    return (getState(key) == GLFW_PRESS);
}

bool Input::keyUp(KeyCode key)
{
    bool keyUpThisFrame = false;

    if (_keysPrevious[key] == false)
    {
        keyUpThisFrame = false;
    }
    else if (_keysPrevious[key] == true && _keys[key] == false)
    {
        keyUpThisFrame = true;
    }
    else if (_keysPrevious[key] == true && _keys[key] == true)
    {
        keyUpThisFrame = false;
    }

    _keysPrevious[key] = _keys[key];

    return keyUpThisFrame;
}

bool Input::getKey(KeyCode key)
{
    return _keys[key];
}

bool Input::mouseButtonDown(MouseButton button)
{
    bool buttonDownThisFrame = false;

    if (_buttonsPrevious[button] == true)
    {
        buttonDownThisFrame = false;
    }
    else if (_buttonsPrevious[button] == false && _buttons[button] == true)
    {
        buttonDownThisFrame = true;
    }
    else if (_buttonsPrevious[button] == false && _buttons[button] == false)
    {
        buttonDownThisFrame = false;
    }

    _buttonsPrevious[button] = _buttons[button];

    return buttonDownThisFrame;
}

bool Input::mouseButtonPressed(MouseButton button)
{
    return (getState(button) == GLFW_PRESS);
}

bool Input::mouseButtonUp(MouseButton button)
{
    bool buttonUpThisFrame = false;

    if (_buttonsPrevious[button] == false)
    {
        buttonUpThisFrame = false;
    }
    else if (_buttonsPrevious[button] == true && _buttons[button] == false)
    {
        buttonUpThisFrame = true;
    }
    else if (_buttonsPrevious[button] == true && _buttons[button] == true)
    {
        buttonUpThisFrame = false;
    }

    _buttonsPrevious[button] = _buttons[button];

    return buttonUpThisFrame;
}

void antisocial::input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    Input::_keys[key] = (action != GLFW_RELEASE);
}

void antisocial::input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    Input::_buttons[button] = (action != GLFW_RELEASE);
}
