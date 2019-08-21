#include "scop.h"

float yaw = -90.0f;
float pitch = 0;

void	dump_parced_object(t_obj obj, bool debug)
{
	printf("[Dump Points array of length %d]\n", obj.points_len);
	if (debug) {
		for (int i = 0; i < obj.points_len; i++) {
			printf("v[%d]\t%+f %+f %+f\n", i, obj.points[i][0], obj.points[i][1], obj.points[i][2]);
		}
	}
	printf("[Dump Normals array of length %d]\n", obj.normals_len);
	if (debug) {
		for (int i = 0; i < obj.normals_len; i++) {
			printf("f[%d]\t%f %f %f\n", i, obj.normals[i][0], obj.normals[i][1], obj.normals[i][2]);
		}
	}
	printf("[Dump Vertex array of length %d]\n", obj.vertices_len);
	if (debug) {
		// for (int i = 0; i < obj.indices_len; i++) {
		// 	printf("f[%d]\t%d %d %d\n", i, obj.indices[i][0], obj.indices[i][1], obj.indices[i][2]);
		// }
	}
}

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
		// static uint32_t num = 0;
		// printf("Mouse clicked %d %f %f\n", ++num, yoffset ,xoffset);
		yaw   += xoffset;
		pitch -= yoffset;
		if(pitch > 89.0f)
			pitch =  89.0f;
		if(pitch < -89.0f)
			pitch = -89.0f;
	}
}


int main(void)
{
	t_gl_env	env = {};
	t_camera	cam = {};
	t_obj		obj = {};

	ft_printf("####       Start        ####\n");
	ft_time_start();
	parse_obj_file(TEAPOT2_OBJ_PATH, &obj);
	ft_time_end("Parse time");
	dump_parced_object(obj, false);
	if (!gl_env_init("Scop", 1600, 900, &env))
		return (gl_error_report("OpenGL could not init :(", -1));
	glfwSetCursorPosCallback(env.window, mouse_callback);
	print_gl_info();

	init_buffers(&obj);
	if (create_shader_prog(&(env.shader_prog)))
	{
		create_camera(&env, &cam, &obj);
		load_camera_projection(&cam, 45.0f, CAMERA_PERSPECTIVE, VEC2(0.1f, 10000.0f));

		if (glGetError() != GL_NO_ERROR)
			ft_printf("WARNING glError: %d", glGetError());

		render_loop(&env, &cam, &obj);
	}
	glfwTerminate();
	free(obj.points);
	free(obj.indices);
	ft_printf("#### IT IS FINALLY ENDED! ####\n");
	return (0);
}
