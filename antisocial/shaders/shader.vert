#version 330 core
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 TexCoord;
layout (location = 3) in vec3 Normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 fragPos;
out vec3 fragColor;
out vec2 texCoord;
out vec3 normal;

uniform float time;
uniform float verticeOffset;

void main()
{
	vec3 pos = Pos;
	pos.xyz += Normal.xyz * verticeOffset;

	normal = Normal;
	fragColor = Color;
	texCoord = TexCoord;
    gl_Position = vec4(pos, 1.0f) * model * view * projection;

	fragPos = vec3(model * vec4(pos, 1.0f));
}
