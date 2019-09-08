/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 11:31:52 by tryckylake        #+#    #+#             */
/*   Updated: 2019/09/08 17:17:04 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		obj_transform(t_obj *obj, t_camera *cam)
{
	t_mat4	model;
	t_mat4	view;

	view = mat_look_at(cam->cam_pos, cam->cam_front, cam->cam_up);
	glUniformMatrix4fv(cam->uniform_view_loc, 1, GL_TRUE, (float*)&view);
	model = mat_identity();
	model = mat_translate(model, obj->trans);
	model = mat_rotate(model, VEC3(1, 0, 0), DEG_TO_RAD(obj->rot[0]));
	model = mat_rotate(model, VEC3(0, 1, 0), DEG_TO_RAD(obj->rot[1]));
	model = mat_rotate(model, VEC3(0, 0, 1), DEG_TO_RAD(obj->rot[2]));
	model = mat_scale(model, FLOAT_TO_VEC(g_object_scale));
	glUniformMatrix4fv(cam->uniform_model_loc, 1, GL_TRUE, (float*)&model);
	glUniform4fv(cam->uniform_light_loc, 1, (float*)&(cam->cam_pos));
	glUniform4fv(cam->uniform_obj_color, 1, (float*)&(obj->color));
}

void		render_loop(t_gl_env *env, t_camera *cam, t_obj *obj)
{
	t_vec4		dir;
	uint32_t	uniform_pos_loc;
	uint32_t	uniform_show_tex;

	uniform_show_tex = glGetUniformLocation(env->shader_prog, "u_show_texture");
	uniform_pos_loc = glGetUniformLocation(env->shader_prog, "u_view_pos");
	while (!glfwWindowShouldClose(env->window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		get_delta_time();
		process_input(env->window, cam, obj);
		dir[0] = cos(DEG_TO_RAD(g_pitch)) * cos(DEG_TO_RAD(g_yaw));
		dir[1] = sin(DEG_TO_RAD(g_pitch));
		dir[2] = cos(DEG_TO_RAD(g_pitch)) * sin(DEG_TO_RAD(g_yaw));
		cam->cam_pos = vec_unit(dir) * FLOAT_TO_VEC(cam->cam_rotate_radius);
		glUniform4fv(uniform_pos_loc, 1, (float*)&(cam->cam_pos));
		obj_transform(obj, cam);
		glBindVertexArray(env->vao_object);
		glDrawArrays(GL_TRIANGLES, 0, obj->vertices_len);
		glUniform1f(uniform_show_tex, obj->show_texture);
		glfwSwapBuffers(env->window);
		glfwPollEvents();
	}
}
