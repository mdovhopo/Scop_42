/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 22:21:38 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/23 17:23:26 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "libft.h"
# include "obj_parser.h"

# include <stdio.h>
# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <cglm/cglm.h>

// Camera rotaion stuff

extern float delta_time;

extern float pitch;
extern float yaw;

extern float object_scale;

#define VERTEX_SHADER_PATH		"./src/shaders/vertShader.vert"
#define FRAGMENT_SHADER_PATH	"./src/shaders/fragShader.frag"

#define OBJ_DEFAULT_PATH		"./resources"
#define TEAPOT_OBJ_PATH			OBJ_DEFAULT_PATH "/teapot.obj"
#define TEAPOT2_OBJ_PATH		OBJ_DEFAULT_PATH "/teapot2.obj"
#define FORTY_TWO_OBJ_PATH		OBJ_DEFAULT_PATH "/42.obj"
#define BMW_OBJ_MODEL			OBJ_DEFAULT_PATH "/BMW X5 4.obj"
#define BUGATTI_OBJ_MODEL		OBJ_DEFAULT_PATH "/bugatti.obj"
#define PORSCHE_911_OBJ_MODEL	OBJ_DEFAULT_PATH "/Porsche_911_GT2.obj"

typedef struct	s_gl_env
{
	GLFWwindow	*window;
	uint32_t	w_width;
	uint32_t	w_height;
	uint32_t	shader_prog;
	uint32_t	vao_object;
	uint32_t	vao_floor;
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
	t_vec4		cam_pos;
	t_vec4		cam_front;
	t_vec4		cam_up;
	float		cam_speed;
	uint32_t	cam_rotate_radius;

}				t_camera;

typedef enum	e_camera_type
{
	CAMERA_PERSPECTIVE	= 0x01,
	CAMERA_ORTHOGRAPHIC	= 0x02
}				t_camera_type;

/*
** Init enviroment
*/

bool	gl_env_init(const char *window_name,
				const uint32_t w,
				const uint32_t h,
				t_gl_env *e);
bool	compile_shader(	uint32_t *shader_id,
						const char* source,
						int32_t type,
						const char* name);
bool	link_shader_prog(uint32_t *prog_id, uint32_t *shaders, uint32_t length);
bool	create_shader_prog(uint32_t *prog);
void	init_buffers(t_obj *obj, t_gl_env *e);

/*
** Camera
*/

void	create_camera(t_gl_env *env, t_camera *cam, t_obj *obj);
void	load_camera_projection(	t_camera *cam, float fov,
								t_camera_type type, t_vec4 near_far);

/*
** Main Render
*/

void	render_loop(t_gl_env *env, t_camera *cam, t_obj *obj);

/*
** Utils
*/

void	get_delta_time(void);
void	print_gl_info(void);
ssize_t	get_file_size(const char *path);
char	*read_file(const char *path);

/*
** Error handle
*/

int32_t	gl_error_report(const char *msg, const int32_t exit_code);


#endif
