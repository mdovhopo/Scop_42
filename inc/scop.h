/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 22:21:38 by tryckylake        #+#    #+#             */
/*   Updated: 2019/07/12 11:55:15 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "libft.h"

# include <stdio.h>
# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <cglm/cglm.h>

extern float delta_time;	// Time between current frame and last frame
extern float last_frame; // Time of last frame

// Camera rotaion stuff

extern float pitch;
extern float yaw;

extern float lastX;
extern float lastY;

#define VERTEX_SHADER_PATH		"./src/shaders/vertShader.vert"
#define FRAGMENT_SHADER_PATH	"./src/shaders/fragShader.frag"

typedef struct	s_gl_env
{
	GLFWwindow	*window;
	uint32_t	w_width;
	uint32_t	w_height;
	uint32_t	shader_prog;
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
	t_vec4		cam_pos;
	t_vec4		cam_front;
	t_vec4		cam_up;
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
void	init_buffers(void);

/*
** Camera
*/

void	create_camera(t_gl_env *env, t_camera *cam);
void	load_camera_projection(	t_camera *cam, float fov,
								t_camera_type type, t_vec4 near_far);

/*
** Main Render
*/

void	render_loop(t_gl_env *env, t_camera *cam);

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

int32_t		gl_error_report(const char *msg, const int32_t exit_code);

#endif
