/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 22:21:38 by tryckylake        #+#    #+#             */
/*   Updated: 2019/09/08 17:33:56 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "libft.h"
# include "obj_parser.h"

# include "stb_image.h"

# include <stdio.h>
# include <glad/glad.h>
# include <GLFW/glfw3.h>

extern float g_dt;

extern float g_pitch;
extern float g_yaw;

extern float g_object_scale;

# define VERTEX_SHADER_PATH		"./src/shaders/vertShader.vert"
# define FRAGMENT_SHADER_PATH	"./src/shaders/fragShader.frag"

# define OBJ_DEFAULT_PATH		"./resources"
# define TEAPOT_OBJ_PATH		OBJ_DEFAULT_PATH "/teapot.obj"
# define TEAPOT2_OBJ_PATH		OBJ_DEFAULT_PATH "/teapot2.obj"
# define FORTY_TWO_OBJ_PATH		OBJ_DEFAULT_PATH "/42.obj"
# define BMW_OBJ_MODEL			OBJ_DEFAULT_PATH "/BMW X5 4.obj"
# define BUGATTI_OBJ_MODEL		OBJ_DEFAULT_PATH "/bugatti.obj"
# define PORSCHE_911_OBJ_MODEL	OBJ_DEFAULT_PATH "/Porsche_911_GT2.obj"

# define DEFAULT_OBJECT_COLOR	VEC(0.337254f, 0.396078f, 0.450980f, 1.0f)
# define MOUSE_SENSITIVITY		0.05f

typedef struct	s_gl_env
{
	GLFWwindow	*window;
	uint32_t	w_width;
	uint32_t	w_height;
	uint32_t	shader_prog;
	uint32_t	vao_object;
	char		*obj_file_name;
	char		*window_name;
}				t_gl_env;

typedef struct	s_camera
{
	uint32_t	width;
	uint32_t	height;
	t_mat4		m_proj;
	t_mat4		m_view;
	uint32_t	uniform_model_loc;
	uint32_t	uniform_view_loc;
	uint32_t	uniform_proj_loc;
	uint32_t	uniform_light_loc;
	uint32_t	uniform_obj_color;
	t_vec4		cam_pos;
	t_vec4		cam_front;
	t_vec4		cam_up;
	float		cam_speed;
	uint32_t	cam_rotate_radius;

}				t_camera;

/*
** Init enviroment
*/

bool			gl_env_init(t_gl_env *e);
bool			compile_shader(uint32_t *shader_id,
						const char *source,
						int32_t type,
						const char *name);
bool			link_shader_prog(uint32_t *prog_id,
									uint32_t *shaders, uint32_t length);
bool			create_shader_prog(uint32_t *prog);
void			init_buffers(t_obj *obj, t_gl_env *e);

/*
** Camera
*/

void			create_camera(t_gl_env *env, t_camera *cam, t_obj *obj);
void			load_camera_projection(t_camera *cam,
									float fov, t_vec4 near_far);

/*
** Main Render
*/

void			render_loop(t_gl_env *env, t_camera *cam, t_obj *obj);

/*
** Utils
*/
void			parse_flags(t_gl_env *env, t_obj *obj, int argc, char **argv);
void			get_delta_time(void);
void			print_gl_info(void);
ssize_t			get_file_size(const char *path);
char			*read_file(const char *path);

/*
** Error handle
*/

int32_t			gl_error_report(const char *msg, const int32_t exit_code);

/*
** Parse comandline args
*/

typedef enum	e_handler_type
{
	SHOW_HELP = 0,
	GET_FILE,
	GET_WINDOW_NAME,
	GET_COLOR,
	GET_SCREEN_SIZE,
	GET_TEXTURE,
	UNKNOWN_FLAG
}				t_handler_type;

void			show_help(t_gl_env *env, t_obj *obj,
											int *curr_arg, char *parm_name);
void			get_file(t_gl_env *env, t_obj *obj,
											int *curr_arg, char *parm_name);
void			get_window_name(t_gl_env *env, t_obj *obj,
											int *curr_arg, char *parm_name);
void			get_color(t_gl_env *env, t_obj *obj,
											int *curr_arg, char *parm_name);
void			get_screen_size(t_gl_env *env, t_obj *obj,
											int *curr_arg, char *parm_name);
void			get_texture(t_gl_env *env, t_obj *obj,
											int *curr_arg, char *parm_name);

/*
**	Events handler
*/

void			process_input(GLFWwindow *window, t_camera *cam, t_obj *obj);

#endif
