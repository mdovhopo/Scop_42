#include <stdio.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

void error_callback(int error, const char* description)
{
    printf("Error: %s\n", description);
}

const float vertexies[] = {
	-0.5, -0.5,
	 0,	   0.5,
	 0.5  -0.5
};

void	print_gl_info(void) {
	printf("VENDOR: %s\nRENDERER %s\nVERSION %s\nSHADING LANGUAGE V %s\nEXT %s\n", 
		glGetString(GL_VENDOR),
		glGetString(GL_RENDERER),
		glGetString(GL_VERSION), 
		glGetString(GL_SHADING_LANGUAGE_VERSION),
		glGetString(GL_EXTENSIONS)
	);
}

int main(void)
{
	printf("####       Start        ####\n");
	if (!glfwInit()) {
		return (0);
	}
	glfwSetErrorCallback(error_callback);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Scop", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return (-1);
	}
	
	print_gl_info();

	glfwMakeContextCurrent(window);
	// uint32_t buffer;
	// glGenBuffers(1, &buffer);
	// glBindBuffer(GL_ARRAY_BUFFER, buffer);
	// glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertexies, GL_STATIC_DRAW);

	
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	printf("#### IT IS FINNALY END! ####\n");
	return (0);
}