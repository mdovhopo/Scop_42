/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_camera_projection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 22:52:51 by tryckylake        #+#    #+#             */
/*   Updated: 2019/07/11 23:07:32 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

// TODO make camera projection depend on type

void	load_camera_projection(	t_camera *cam, float fov,
								t_camera_type type, t_vec4 near_far)
{
	t_mat4	proj;
	float	aspect;

	aspect = cam->width / (float)(cam->height);
	proj = mat_identity();
	proj = mat_perspective(DEG_TO_RAD(fov), aspect, near_far[0], near_far[1]);
	glUniformMatrix4fv(cam->uniform_proj_loc, 1, GL_TRUE, (float*)&proj);
}
