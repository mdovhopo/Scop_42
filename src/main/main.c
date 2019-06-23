#include "scop.h"

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

const float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

int main(void)
{
	GLFWwindow	*window;
	char		*vertShaderCode;
	char		*fragShaderCode;
	uint32_t	vertShaderId;
	uint32_t	fragShaderId;
	uint32_t	shaderProg;

	printf("####       Start        ####\n");
	if (!gl_init("Scop", 800, 600, &window))
		return (gl_error_report("OpenGL could not init :(", -1));
	print_gl_info();
	// Read shaders from source

	// TODO make gl_env struct and move all this stuff to gl_init
	fragShaderCode = read_file(FRAGMENT_SHADER_PATH);
	vertShaderCode = read_file(VERTEX_SHADER_PATH);

	// Compile shaders
	if(!compile_shader(&vertShaderId, vertShaderCode, GL_VERTEX_SHADER))
		return (-1);
	if (!compile_shader(&fragShaderId, fragShaderCode, GL_FRAGMENT_SHADER))
		return (-1);
	free(vertShaderCode);
	free(fragShaderCode);
	// Link Program
	if (!link_shader_prog(&shaderProg, (uint32_t[]){vertShaderId, fragShaderId}, 2))
		return (-1);

	uint32_t vbo;
	glGenBuffers(1, &vbo);

	uint32_t vao;
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(vao);
	glUseProgram(shaderProg);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteShader(vertShaderId);
	glDeleteShader(fragShaderId);  
	glfwTerminate();
	printf("#### IT IS FINNALY ENDED! ####\n");
	return (0);
}