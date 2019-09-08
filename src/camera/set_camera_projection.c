/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_camera_projection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 14:31:21 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/09/08 17:26:56 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	load_camera_projection(t_camera *cam, float fov, t_vec4 near_far)
{
	t_mat4	proj;
	float	aspect;

	aspect = cam->width / (float)(cam->height);
	proj = mat_identity();
	proj = mat_perspective(DEG_TO_RAD(fov), aspect, near_far[0], near_far[1]);
	glUniformMatrix4fv(cam->uniform_proj_loc, 1, GL_TRUE, (float*)&proj);
}
