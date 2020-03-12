#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
 
out vec4 frag_color;

uniform sampler2D texSampler1;
uniform vec3 lightColor; 
uniform vec3 lightPos;

void main()
{
	float ambientFactor = 0.1f;
	vec3 ambient = lightColor * ambientFactor;
	

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float NDotL = max(dot(normal,lightDir),0.0f);
	vec3 diffuse = lightColor * NDotL;

	vec3 specular = vec3(0.0f);

	vec4 texel = texture(texSampler1,TexCoord);

	frag_color = vec4(ambient + diffuse + specular,1.0f) * texel;
};  