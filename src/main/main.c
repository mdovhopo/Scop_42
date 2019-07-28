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

const char *first_tokens[] = {
	"v",
	"f",
	"mtllib",
	"usemtl",
	"o",
	"s",
	NULL
};

void	parse_vertex()
{
	printf("parse vertex\n");
}

void	parse_index()
{
	printf("parse index\n");
}

void	parse_mtllib()
{
	printf("parse mtllib\n");
}

void	parse_usemtl()
{
	printf("parse usemtl\n");
}

void	parse_object()
{
	printf("parse object\n");
}

void	parse_smooth()
{
	printf("parse smooth\n");
}

void (*line_parsers[])() = {
	&parse_vertex,
	&parse_index,
	&parse_mtllib,
	&parse_usemtl,
	&parse_object,
	&parse_smooth
};

int32_t	find_str_in_array(char** arr, char* to_find)
{
	int32_t i = 0;
	while (*arr != NULL)
	{
		if (ft_strequ(*arr, to_find) == 1)
			return (i);
		i++;
		arr++;
	}
	return (-1);
}

void	free_2d_arr(void **arr)
{
	void *tmp;

	while (*arr)
	{
		tmp = *arr;
		arr++;
		free(tmp);
	}
}

int main (void)
{
	int fd = open("/home/tryckylake/UNIT_PROJECTS/Scop_42/resources/42.obj", O_RDONLY);
	char *line = NULL;
	uint32_t line_count = 0;
	t_obj obj;
	while (get_next_line(fd, &line) > 0)
	{
		char *trimmed_line = ft_strtrim(line);
		free(line);
		if (*trimmed_line == '#' || *trimmed_line == 0 || *trimmed_line == '\n') {
			free(trimmed_line);
			line_count++;
			continue;
		}
		char **tokens = ft_strsplit(trimmed_line, ' ');
		t_first_token token_id;
		printf("%d: |%s| %d\n", ++line_count, tokens[0], *trimmed_line);
		if ((token_id = find_str_in_array((char**)first_tokens, tokens[0])) < 0)
		{
			printf(RED"ERROR"RESET" %d: %s\nUnexpected token: [%s]\n", line_count, trimmed_line, tokens[0]);
			break;
		}
		line_parsers[token_id]();
		free_2d_arr((void**)tokens);
		free(trimmed_line);
	}
	return (0);
}

int main_1(void)
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
