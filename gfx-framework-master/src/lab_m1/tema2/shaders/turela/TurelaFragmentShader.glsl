#version 330

// TODO: get values from fragment shader
in vec3 world_position;
in vec3 world_normal;
layout(location = 0) out vec4 out_color;

uniform int tankType;

uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform int HP;
uniform int maxHP;

void main()
{
	// TODO: write pixel out color
	vec3 color;
	if (tankType == 0) {
		color = vec3(45/255.f, 103/255.f, 158/255.f);
	} else {
		color = vec3(158/255.f, 45/255.f, 45/255.f);
	}

	float darknessFactor = (float(HP) / float(maxHP)) ;
	color *= darknessFactor;
	float light = 0;
	
	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);

	// Define ambient light component
	float ambient_light = 0.5;

	// Compute diffuse light component
	float diffuse_light = material_kd * max(dot(normalize(N), L), 0);

	// Compute specular light component
	float specular_light = 0;

	if (diffuse_light > 0)
	{
		specular_light = material_ks * pow(max(dot(normalize(N), H), 0), material_shininess);
	}

	light = ambient_light + diffuse_light + specular_light;		
	color *= light;
	
    out_color =  vec4(color, 1.0);
}