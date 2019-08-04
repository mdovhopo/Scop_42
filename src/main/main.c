#include "scop.h"
#include <time.h>
clock_t start;

void	time_start()
{
	start = clock();
}

void	time_end(const char *name)
{
	double cpu_time_used;
	clock_t end;
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("%s: [%fms]\n", name, cpu_time_used); 
}

float delta_time = 0.0f;
float last_frame = 0.0f;

float yaw = -90.0f;
float pitch = 0;

float lastX;
float lastY;
bool firstMouse = true;

void	dump_parced_object(t_obj obj)
{
	printf("[Dump Vertex array of length %d]\n", obj.vert_len);
	for (int i = 0; i < obj.vert_len; i++) {
		printf("v[%d]\t%+f %+f %+f\n", i, obj.vertices[i][0], obj.vertices[i][1], obj.vertices[i][2]);
	}
	printf("[Dump Index array of length %d]\n", obj.indices_len);
	for (int i = 0; i < obj.indices_len; i++) {
		printf("f[%d]\t%d %d %d\n", i, obj.indices[i][0], obj.indices[i][1], obj.indices[i][2]);
	}
}

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


int main(void)
{
	t_gl_env	env = {};
	t_camera	cam = {};
	t_obj		obj = {};

	// ft_printf("####       Start        ####\n");
	time_start();
	parse_obj_file(TEAPOT2_OBJ_PATH, &obj);
	time_end("Parse time");
	// dump_parced_object(obj);
	if (!gl_env_init("Scop", 800, 600, &env))
		return (gl_error_report("OpenGL could not init :(", -1));
	glfwSetCursorPosCallback(env.window, mouse_callback);
	print_gl_info();

	init_buffers(&obj);
	create_shader_prog(&(env.shader_prog));
	create_camera(&env, &cam);
	load_camera_projection(&cam, 45.0f, CAMERA_PERSPECTIVE, VEC2(0.1f, 100.0f));

	if (glGetError() != GL_NO_ERROR)
		ft_printf("WARNING glError: %d", glGetError());

	render_loop(&env, &cam, &obj);
	glfwTerminate();
	free(obj.vertices);
	free(obj.indices);
	ft_printf("#### IT IS FINALLY ENDED! ####\n");
	return (0);
}
