#version 410 core

layout (location = 0) in vec4 a_pos;
layout (location = 1) in vec4 a_normal;
// attribute vec4 a_pos;
// attribute vec4 a_normal;

out vec4 normal;
out vec4 frag_pos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

void main() {
	gl_Position = u_proj * u_view * u_model * a_pos;
	frag_pos = u_model * a_pos; 
	normal = u_model * a_normal;
}
