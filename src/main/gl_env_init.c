#include "scop.h"

void	error_callback(int error, const char* description)
{
	ft_printf("Error: %s\n", description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (yoffset) {
		if (yoffset < 0) {
			object_scale = clamp(0.1f, 100.0f, object_scale += 0.1f);
		} else {
			object_scale = clamp(0.1f, 100.0f, object_scale -= 0.1f);
		}
	}
}

float yaw = -90.0f;
float pitch = 0;
float lastX = 400;
float lastY = 300;


float delta_time = 0.0f;
float last_frame = 0.0f;

float lastX;
float lastY;

bool firstMouse = true;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; 
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		yaw   += xoffset;
		pitch -= yoffset;
		pitch = clamp(-89.0f, 89.0f, pitch);
	}
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

bool	gl_env_init(t_gl_env *e)
{
	GLFWmonitor*		monitor;
	const GLFWvidmode*	mode;

	if (!glfwInit())
		return (false);
	monitor = NULL;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// debug
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);  
	glfwSetErrorCallback(error_callback);
	if (e->w_width == 0 || e->w_height == 0) {
		monitor = glfwGetPrimaryMonitor();
		mode = glfwGetVideoMode(monitor);
		e->w_width = mode->width;
		e->w_height = mode->height;
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		e->window = glfwCreateWindow(e->w_width, e->w_height, e->window_name, monitor, NULL);
		glfwSetWindowMonitor(e->window, monitor, 0, 0, e->w_width, e->w_height, mode->refreshRate);
	}
	else
		e->window = glfwCreateWindow(e->w_width, e->w_height, e->window_name, NULL, NULL);
	if (!(e->window))
		return (gl_error_report("Could not create window :(", 0));
	glfwGetFramebufferSize(e->window, (int*)&e->w_width, (int*)&e->w_height);
	glfwMakeContextCurrent(e->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return (gl_error_report("Could not load GL functions :(", 0));
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, e->w_width, e->w_height);
	glfwSetInputMode(e->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
	glfwSetFramebufferSizeCallback(e->window, framebuffer_size_callback);
	glfwSetScrollCallback(e->window, scroll_callback);
	glfwSetCursorPosCallback(e->window, mouse_callback);
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
