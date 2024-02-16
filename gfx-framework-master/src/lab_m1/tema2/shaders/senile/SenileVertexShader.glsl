#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform int HP;
uniform int maxHP;

// Output value to fragment shader
out vec3 world_position;
out vec3 world_normal;



void main() {
    // Compute world space vectors
    world_position = (Model * vec4(v_position, 1)).xyz;
    world_normal = normalize(vec3(Model * vec4(v_normal, 0.0)));

    float flattenScale = 1.0 - float(HP) / float(maxHP) ;

    // Simple sine wave deformation
    float displacement = sin(v_position.x * 0.1f * flattenScale + v_position.y * 0.1f * flattenScale +  v_position.z * 0.1f * flattenScale);

    vec3 deformed_position = v_position + displacement;

    gl_Position = Projection * View * Model * vec4(deformed_position, 1.0);
}
