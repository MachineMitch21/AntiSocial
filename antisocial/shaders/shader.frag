#version 330 core
out vec4 FragColor;

in vec3 fragPos;
in vec3 fragColor;
in vec2 texCoord;
in vec3 normal;

uniform sampler2D tex;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 ambientLightColor;
uniform float ambientIntensity = 0.25f;

void main()
{
    vec3 ambient = ambientIntensity * ambientLightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse);

    FragColor = texture(tex, texCoord) * vec4(result, 1.0f);
}
