#version 410 core

// layout (location = 0) in vec3 pos;
// layout (location = 1) in vec3 color;
attribute vec4 a_pos;
attribute vec4 a_normal;

out vec4 vertex_color;
out vec4 normal;
out vec4 frag_pos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

void main() {
	vec4 object_color = vec4(0.337254f, 0.396078f, 0.450980f, 1.0f);
	gl_Position = u_proj * u_view * u_model * a_pos;
	vertex_color = object_color;
	frag_pos = u_model * a_pos; 
	normal = u_model * a_normal;
}
