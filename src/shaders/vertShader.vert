#version 410 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec4 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(pos, 1.0f);
	// gl_Position = vec4(pos, 1.0f);
	// vertexColor = vec4(view[2].w, 0, 0,  1);
	// vertexColor = vec4(test[3].x, test[3].y, test[3].z, 1);
	vertexColor = vec4(color, 1);
}
