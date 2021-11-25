#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;


uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform sampler2D texture_diffuse1;

void main()
{    
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