#version 330 core
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 fragPos;
out vec3 fragColor;

uniform float time;

void main()
{
    fragPos = vec3(model * vec4(Pos, 1.0f));
    fragColor = Color;
    gl_Position = vec4(Pos, 1.0f) * model * view * projection;
}
