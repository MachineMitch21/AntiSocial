#version 330 core
out vec4 FragColor;

in vec3 fragPos;
in vec3 fragColor;
in vec2 texCoord;
in vec3 normal;

uniform sampler2D tex;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 viewPos;

uniform vec3 ambientLightColor;
uniform float ambientIntensity = 0.25f;

uniform float specularStrength = 0.5f;


vec3 getDiffuseContribution();
vec3 getSpecularContribution();


void main()
{
    vec3 ambient = ambientIntensity * ambientLightColor;

    vec3 diffuseContribution = getDiffuseContribution();
    vec3 specularContribution = getSpecularContribution();

    vec3 lightContribution = diffuseContribution + specularContribution;

    vec3 result = (ambient + lightContribution);

    FragColor = texture(tex, texCoord) * vec4(result, 1.0f);
}

vec3 getDiffuseContribution()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    return diffuse;
}

vec3 getSpecularContribution()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    vec3 specular = specularStrength * spec * lightColor;

    return specular;
}
