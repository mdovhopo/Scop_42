#include "scop.h"

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}

const float vertices[] = {
// 	 x		y	  z		 r	   g	 b
     0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // top right
     0.5f, -0.5f, 0.0f,  0.0f, 0.6f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // bottom left
    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f, // top left 
};

const uint32_t indices[] = {
	0, 1, 3,
	1, 2, 3
};

int main(void)
{
	GLFWwindow	*window;
	char		*vertShaderCode;
	char		*fragShaderCode;
	uint32_t	vertShaderId;
	uint32_t	fragShaderId;
	uint32_t	shaderProg;

	ft_printf("####       Start        ####\n");
	if (!gl_init("Scop", 800, 600, &window))
		return (gl_error_report("OpenGL could not init :(", -1));
	print_gl_info();
	// Read shaders from source

	// TODO make gl_env struct and move all this stuff to gl_init
	fragShaderCode = read_file(FRAGMENT_SHADER_PATH);
	vertShaderCode = read_file(VERTEX_SHADER_PATH);

	// Compile shaders
	if(!compile_shader(&vertShaderId, vertShaderCode, GL_VERTEX_SHADER, VERTEX_SHADER_PATH))
		return (-1);
	if (!compile_shader(&fragShaderId, fragShaderCode, GL_FRAGMENT_SHADER, FRAGMENT_SHADER_PATH))
		return (-1);
	free(vertShaderCode);
	free(fragShaderCode);
	// Link Program
	if (!link_shader_prog(&shaderProg, (uint32_t[]){vertShaderId, fragShaderId}, 2))
		return (-1);
	glDeleteShader(vertShaderId);
	glDeleteShader(fragShaderId);  

	uint32_t vao; // vertex_attrib_arr
	uint32_t ebo; // element_buffer_obj
	uint32_t vbo; // vertex_buffer_object
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	// glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glUseProgram(shaderProg);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	ft_printf("#### IT IS FINNALY ENDED! ####\n");
	return (0);
}