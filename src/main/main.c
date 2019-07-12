#include "scop.h"

float delta_time = 0.0f;
float last_frame = 0.0f;

float yaw = -90.0f;
float pitch = 0;

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

	yaw   += xoffset;
	pitch += yoffset;
	if(pitch > 89.0f)
		pitch =  89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;
}

const uint32_t indices[] = {
	0, 1, 3,
	1, 2, 3
};

int main(void)
{
	t_gl_env	env = {};
	t_camera	cam = {};

	ft_printf("####       Start        ####\n");
	if (!gl_env_init("Scop", 800, 600, &env))
		return (gl_error_report("OpenGL could not init :(", -1));
	glfwSetCursorPosCallback(env.window, mouse_callback);
	print_gl_info();

	init_buffers();
	create_shader_prog(&(env.shader_prog));
	create_camera(&env, &cam);
	load_camera_projection(&cam, 45.0f, CAMERA_PERSPECTIVE, VEC2(0.1f, 100.0f));

	if (glGetError() != GL_NO_ERROR)
		ft_printf("WARNING glError: %d", glGetError());

	render_loop(&env, &cam);
	glfwTerminate();
	ft_printf("#### IT IS FINALLY ENDED! ####\n");
	return (0);
}
