/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 22:49:43 by tryckylake        #+#    #+#             */
/*   Updated: 2019/07/26 16:32:20 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	create_camera(t_gl_env *env, t_camera *cam)
{
	cam->uniform_model_loc = glGetUniformLocation(env->shader_prog, "model");
	cam->uniform_proj_loc = glGetUniformLocation(env->shader_prog, "proj");
	cam->uniform_view_loc = glGetUniformLocation(env->shader_prog, "view");
	cam->width = env->w_width;
	cam->height = env->w_height;
	cam->cam_pos = VEC3(0, 0, 5);
	cam->cam_front = VEC3(0, 0, -1);
	cam->cam_up = VEC3(0, 1, 0);
}
