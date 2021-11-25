#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

varying vec4 FragColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform sampler2D texture_diffuse1;

void main()
{
    vec3 Normal = mat3(transpose(inverse(model))) * aNormal;
    vec2 TexCoords = aTexCoords;    
    vec3 FragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    float specularStrength = 0.5;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos-FragPos);
    vec3 viewDir = normalize(viewPos-FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength*lightColor;
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = 0.5*diff * lightColor;
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    
    vec4 result = vec4((ambient+diffuse+specular),1.0);
    FragColor = result*texture(texture_diffuse1, TexCoords);
}