#version 410 core

// layout (location = 0) in vec3 pos;
// layout (location = 1) in vec3 color;
attribute vec4 pos;
// attribute vec3 color;

out vec4 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
	gl_Position = proj * view * model * pos;
	vertexColor = vec4(0.337254f, 0.396078f, 0.450980f, 1.0f);
}
