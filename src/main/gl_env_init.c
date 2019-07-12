#include "scop.h"

void	error_callback(int error, const char* description)
{
	ft_printf("Error: %s\n", description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

float lastX = 400, lastY = 300;



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
void APIENTRY glDebugOutput(GLenum source, 
                            GLenum type, 
                            GLuint id, 
                            GLenum severity, 
                            GLsizei length, 
                            const GLchar *message, 
                            const void *userParam)
{
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

    printf("---------------\n");
    printf("Debug message (%d) %s\n",id , message);

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             printf("Source: API"); break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   printf("Source: Window System"); break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: printf("Source: Shader Compiler"); break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     printf("Source: Third Party"); break;
        case GL_DEBUG_SOURCE_APPLICATION:     printf("Source: Application"); break;
        case GL_DEBUG_SOURCE_OTHER:           printf("Source: Other"); break;
    };
	printf("\n");

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               printf("Type: Error"); break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: printf("Type: Deprecated Behaviour"); break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  printf("Type: Undefined Behaviour"); break; 
        case GL_DEBUG_TYPE_PORTABILITY:         printf("Type: Portability"); break;
        case GL_DEBUG_TYPE_PERFORMANCE:         printf("Type: Performance"); break;
        case GL_DEBUG_TYPE_MARKER:              printf("Type: Marker"); break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          printf("Type: Push Group"); break;
        case GL_DEBUG_TYPE_POP_GROUP:           printf("Type: Pop Group"); break;
        case GL_DEBUG_TYPE_OTHER:               printf("Type: Other"); break;
    };
	printf("\n");
    
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         printf("Severity: high"); break;
        case GL_DEBUG_SEVERITY_MEDIUM:       printf("Severity: medium"); break;
        case GL_DEBUG_SEVERITY_LOW:          printf("Severity: low"); break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: printf("Severity: notification"); break;
    };
	printf("\n");
}
#endif

bool	gl_env_init(const char *window_name,
				const uint32_t w,
				const uint32_t h,
				t_gl_env *e)
{
	int width;
	int height;

	e->w_width = w;
	e->w_height = h;
	if (!glfwInit()) {
		return (false);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //for mac compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// debug
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);  
	glfwSetErrorCallback(error_callback);
	e->window = glfwCreateWindow(w, h, "Scop", NULL, NULL);
	if (!(e->window))
		return (gl_error_report("Could not create window :(", 0));
	glfwGetFramebufferSize(e->window, &width, &height);
	glfwMakeContextCurrent(e->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return (gl_error_report("Could not load GL functions :(", 0));
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
	glClearColor(68 / (float)255, 85 / (float)255, 90 / (float)255, 1.0f);
	glfwSetInputMode(e->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
	glfwSetFramebufferSizeCallback(e->window, framebuffer_size_callback);
	# if !defined(__MACH__) && !defined(__APPLE__) // on MacOS i have OpenGL 4.1 and this stuff is not working on <= 4.4
	// glDebugMessageCallback(MessageCallback, 0);
	GLint flags = 0; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
		glDebugMessageCallback(glDebugOutput, NULL);
		glDebugMessageControl(GL_DEBUG_SOURCE_API, 
                      GL_DEBUG_TYPE_ERROR, 
                      GL_DEBUG_SEVERITY_HIGH, 0, NULL, GL_TRUE);

	#endif
	return (true);
}
