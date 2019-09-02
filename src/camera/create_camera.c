/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 14:30:46 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/09/02 14:30:50 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#define GET_UNIFORM glGetUniformLocation

void	create_camera(t_gl_env *env, t_camera *cam, t_obj *obj)
{
	int i;

	i = 0;
	cam->uniform_model_loc = GET_UNIFORM(env->shader_prog, "u_model");
	cam->uniform_proj_loc = GET_UNIFORM(env->shader_prog, "u_proj");
	cam->uniform_view_loc = GET_UNIFORM(env->shader_prog, "u_view");
	cam->uniform_light_loc = GET_UNIFORM(env->shader_prog, "u_light_pos");
	cam->uniform_obj_color = GET_UNIFORM(env->shader_prog, "u_obj_color");
	cam->width = env->w_width;
	cam->height = env->w_height;
	cam->cam_speed =
			fabsf(obj->farest_point[0]) +
			fabsf(obj->farest_point[1]) +
			fabsf(obj->farest_point[2]);
	cam->cam_rotate_radius = vec_mag(obj->farest_point) * 2;
	cam->cam_pos = VEC3(
		0,
		cam->cam_rotate_radius * 5,
		(int32_t)cam->cam_rotate_radius * -2);
	cam->cam_front = VEC3(0, 0, 0);
	cam->cam_up = VEC3(0, 1, 0);
	glUniform4fv(cam->uniform_light_loc, 1, (float*)&(cam->cam_pos));
}
