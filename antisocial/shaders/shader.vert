#version 330 core
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 fragColor;
out vec2 texCoord;

void main()
{
	fragColor = Color;
	texCoord = TexCoord;
    gl_Position = vec4(Pos, 1.0f) * model * view * projection;
}
