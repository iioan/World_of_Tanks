#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform int light_type;
uniform float cutoff_angle;

// TODO(student): Declare any other uniforms
uniform vec3 object_color;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
	vec3 color = vec3(0, 0, 0);
	float light = 0;
	
	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);

	// Define ambient light component
	float ambient_light = 0.25;

	// Compute diffuse light component
	float diffuse_light = material_kd * max(dot(normalize(N), L), 0);

	// Compute specular light component
	float specular_light = 0;

	if (diffuse_light > 0)
	{
		specular_light = material_ks * pow(max(dot(normalize(N), H), 0), material_shininess);
	}

	light = ambient_light + diffuse_light + specular_light;		
	color += object_color * light;
	
    out_color =  vec4(color, 1.0);
}
