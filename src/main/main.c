#include "scop.h"
#include <time.h>
clock_t start;

void	time_start()
{
	start = clock();
}

void	time_end()
{
	double cpu_time_used;
	clock_t end;
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time: [%fms]\n", cpu_time_used); 
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

const char *first_tokens[] = {
	"v",
	"f",
	"mtllib",
	"usemtl",
	"o",
	"s",
	NULL
};

void	throw_parsing_error(uint32_t line_count, char *token, char *msg)
{
	ft_printf(RED"Parsing Error: "RESET
			"line:%d Unexpected token: %s\n", line_count, token);
	if (msg)
		ft_printf(CYN"\n%s\n"RESET, msg);
	ft_printf(GRN"\nLearn more about .obj format:\n"RESET
			BLU"https://en.wikipedia.org/wiki/Wavefront_.obj_file\n"RESET);
	exit(-1);
}

void	parse_vertex(char** tokens, t_obj *obj, uint32_t line_count)
{
	t_vec4	v;
	int		i;
	int		err;

	v = VEC3(0.0f, 0.0f, 0.0f);
	i = -1;
	while (tokens[++i])
	{
		v[i] = ft_parse_float(tokens[i], &err);
		if (err)
			throw_parsing_error(line_count, tokens[i], NULL);
		if (i > 3)
			throw_parsing_error(line_count, tokens[i],
				"Expected no more then 4 float values");
	}
	if (i < 3)
		throw_parsing_error(line_count, tokens[i], 
				"Expected at least 3 float values");
	obj->vertices = ft_array_push(obj->vertices, &v, sizeof(t_vec4), obj->vert_len++);
}

void	parse_index(char** tokens, t_obj *obj, uint32_t line_count)
{
	t_veci4	v;
	int		length;
	int		err;
	int		i;

	v = VECI3(0, 0, 0);
	length = -1;
	while(tokens[++length])
		;
	if (length < 3)
		throw_parsing_error(line_count, tokens[length],
			"Expected at least 3 integer values.");
	i = 1;
	while (++i < length)
	{
		v[0] = ft_parse_int(tokens[0], &err);
		if (err)
			throw_parsing_error(line_count, tokens[0], NULL);
		v[1] = ft_parse_int(tokens[i - 1], &err);
		if (err)
			throw_parsing_error(line_count, tokens[i - 1], NULL);
		v[2] = ft_parse_int(tokens[i], &err);
		if (err)
			throw_parsing_error(line_count, tokens[i], NULL);
		// printf("v[%d]\t%+f %+f %+f\n", i - 2, v[0], v[1], v[2]);
		obj->indices = ft_array_push(obj->indices, &v, sizeof(t_vec4), obj->indices_len++);
	}
}

void	parse_mtllib(char** tokens, t_obj *obj, uint32_t line_count)
{
	// printf("parse mtllib\n");
}

void	parse_usemtl(char** tokens, t_obj *obj, uint32_t line_count)
{
	// printf("parse usemtl\n");
}

void	parse_object(char** tokens, t_obj *obj, uint32_t line_count)
{
	// printf("parse object\n");
}

void	parse_smooth(char** tokens, t_obj *obj, uint32_t line_count)
{
	// printf("parse smooth\n");
}

void (*line_parsers[])(char** tokens, t_obj *obj, uint32_t line_count) = {
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


int main(void)
{
	char *line = NULL;
	uint32_t line_count = 1;
	t_obj obj;
	ft_memset(&obj, 0, sizeof(obj));
	time_start();
	while(ft_read_next_line(TEAPOT_OBJ_PATH, &line) > 0)
	{
		char *trimmed_line = ft_strtrim(line);
		// printf("[%d] |%s|\n", line_count, line);
		free(line);
		if (*trimmed_line == '#' || *trimmed_line == 0 || *trimmed_line == '\n') {
			free(trimmed_line);
			line_count++;
			continue;
		}
		char **tokens = ft_strsplit(trimmed_line, ' ');
		t_first_token token_id = find_str_in_array((char**)first_tokens, tokens[0]);
		if (token_id == -1)
			throw_parsing_error(line_count, tokens[0], NULL);
		line_parsers[token_id](tokens + 1, &obj, line_count++);
		free_2d_arr((void**)tokens);
		free(trimmed_line);
	}
	time_end();
	// dump_parced_object(obj);
	free(obj.vertices);
	free(obj.indices);
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
