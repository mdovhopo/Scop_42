#include "scop.h"

void	error_callback(int error, const char* description)
{
	ft_printf("Error: %s\n", description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

# if !defined(__MACH__) && !defined(__APPLE__) // on MacOS i have OpenGL 4.1 and this stuff is not working on <= 4.4
void GLAPIENTRY
MessageCallback(GLenum source,
				GLenum type,
				GLuint id,
				GLenum severity,
				GLsizei length,
				const GLchar* message,
				const void* userParam )
{
	fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
			type, severity, message );
}
#endif

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
	# if !defined(__MACH__) && !defined(__APPLE__) // on MacOS i have OpenGL 4.1 and this stuff is not working on <= 4.4
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
	#endif
	return (true);
}