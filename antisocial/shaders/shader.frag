#version 450 core
out vec4 FragColor;

in vec3 fragColor;
in vec2 texCoord;

uniform sampler2D tex;

void main()
{
    FragColor = texture(tex, texCoord);
}
