#version 410 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec4 vertexColor;

uniform mat4 transform;

void main() {
	gl_Position = transform * vec4(pos, 1.0f);
	vertexColor = vec4(color, 1);
}
