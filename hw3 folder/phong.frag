#version 330 core
out vec4 color;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
// TODO: Replace with your code...
// If gl_Position was set correctly, this gives a totally red cube

// set ambien
float ambStrength = 0.1;
vec3 ambient = ambStrength * lightColor;

// set diffuse
vec3 norm = normalize(Normal);
vec3 lightDirection = normalize(lightPos - FragPos);
float diff = max(dot(norm, lightDirection), 0.0);
vec3 diffuse = diff * lightColor;

// set specular
float specStrength = 0.5;
Vector3d viewDirection = normalize(-FragPos);
Vector3d reflectDirection = reflect(-lightDirection, norm);
float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
Vector3d specular = specStrength * spec * lightColor;

vec3 final = (specular + diffuse + ambient) * objectColor;

color = vec4(final, 1.0f);
}
