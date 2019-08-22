/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 22:49:43 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/21 17:14:16 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	create_camera(t_gl_env *env, t_camera *cam, t_obj *obj)
{
	int i;


	i = 0;
	cam->uniform_model_loc = glGetUniformLocation(env->shader_prog, "u_model");
	cam->uniform_proj_loc = glGetUniformLocation(env->shader_prog, "u_proj");
	cam->uniform_view_loc = glGetUniformLocation(env->shader_prog, "u_view");
	cam->uniform_light_loc = glGetUniformLocation(env->shader_prog, "u_light_pos");
	cam->width = env->w_width;
	cam->height = env->w_height;
	cam->cam_speed = 
			fabsf(obj->farest_point[0]) + 
			fabsf(obj->farest_point[1]) + 
			fabsf(obj->farest_point[2]);
	cam->cam_pos = VEC3(
		0, 
		fabsf(obj->farest_point[1]) / 2, 
		(fabsf(obj->farest_point[2]) + fabsf(obj->farest_point[0])) * 2
	);
	cam->cam_front = VEC3(0, 0, 0);
	cam->cam_up = VEC3(0, 1, 0);
	cam->cam_rotate_radius = vec_mag(obj->farest_point) * 2;
	cam->light_pos = VEC3(
		fabsf(obj->farest_point[0]) * 2, 
		fabsf(obj->farest_point[1]) * 2, 
		(fabsf(obj->farest_point[2]) + fabsf(obj->farest_point[0])) * 2
	);
	glUniform4fv(cam->uniform_light_loc, 1, (float*)&(cam->cam_pos));
}
