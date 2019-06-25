#include "scop.h"

void	error_callback(int error, const char* description)
{
	ft_printf("Error: %s\n", description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool	gl_init(const char *window_name,
				const uint32_t w,
				const uint32_t h,
				GLFWwindow **win)
{
	int width;
	int height;

	if (!glfwInit()) {
		return (false);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //for mac compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSetErrorCallback(error_callback);
	*win = glfwCreateWindow(w, h, "Scop", NULL, NULL);
	if (!*win)
		return (gl_error_report("Could not create window :(", -1));
	glfwGetFramebufferSize(*win, &width, &height);
	glfwMakeContextCurrent(*win);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return (gl_error_report("Could not load GL functions :(", -1));
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(*win, framebuffer_size_callback); 
	return (true);
}