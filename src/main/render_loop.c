/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 11:31:52 by tryckylake        #+#    #+#             */
/*   Updated: 2019/09/02 14:58:48 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void processInput(GLFWwindow *window, t_camera *cam, t_obj *obj)
{
	static bool	key_pressed = false;

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && key_pressed == false)
	{
		obj->show_texture = !obj->show_texture;
		key_pressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE && key_pressed == true)
		key_pressed = false;
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	float cameraSpeed = cam->cam_speed * g_delta_time;
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		obj->rot = VEC3(0, 0, 0);
		obj->trans = VEC3(0, 0, 0);
		cam->cam_pos = VEC3(
			cam->cam_rotate_radius * 2, 
			cam->cam_rotate_radius * 5, 
			(int32_t)cam->cam_rotate_radius * -2
		);
		g_object_scale = 1.0f;
		g_pitch = 0.0f;
		g_yaw = -90.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		obj->manage_type = 1;
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		obj->manage_type = 0;
	if (obj->manage_type == OBJ_ROTATE)
	{
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			obj->rot[0] = loop(-180.0f, 180.0f, obj->rot[0] + 100.0f * g_delta_time);
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			obj->rot[0] = loop(-180.0f, 180.0f, obj->rot[0] - 100.0f * g_delta_time);
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			obj->rot[1] = loop(-180.0f, 180.0f, obj->rot[1] + 100.0f * g_delta_time);
		else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			obj->rot[1] = loop(-180.0f, 180.0f, obj->rot[1] - 100.0f * g_delta_time);
		if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
			obj->rot[2] = loop(-180.0f, 180.0f, obj->rot[2] + 100.0f * g_delta_time);
		else if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
			obj->rot[2] = loop(-180.0f, 180.0f, obj->rot[2] - 100.0f * g_delta_time);
	}
	else if (obj->manage_type == OBJ_TRANSLATE)
	{
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			obj->trans[0] = obj->trans[0] + cameraSpeed;
		else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			obj->trans[0] = obj->trans[0] - cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			obj->trans[1] = obj->trans[1] + cameraSpeed;
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			obj->trans[1] = obj->trans[1] - cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
			obj->trans[2] = obj->trans[2] + cameraSpeed;
		else if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
			obj->trans[2] = obj->trans[2] - cameraSpeed;
	}
}
void	render_loop(t_gl_env *env, t_camera *cam, t_obj *obj)
{
	t_vec4 dir = {};

	while (!glfwWindowShouldClose(env->window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		get_delta_time();
		processInput(env->window, cam, obj);
		dir[0] = cos(DEG_TO_RAD(g_pitch)) * cos(DEG_TO_RAD(g_yaw));
		dir[1] = sin(DEG_TO_RAD(g_pitch));
		dir[2] = cos(DEG_TO_RAD(g_pitch)) * sin(DEG_TO_RAD(g_yaw));
		cam->cam_pos = vec_unit(dir) * FLOAT_TO_VEC(cam->cam_rotate_radius);
		uint32_t uniform_pos_loc = glGetUniformLocation(env->shader_prog, "u_view_pos");
		glUniform4fv(uniform_pos_loc, 1, (float*)&(cam->cam_pos));
		t_mat4 view = mat_look_at(cam->cam_pos, cam->cam_front, cam->cam_up);
		glUniformMatrix4fv(cam->uniform_view_loc, 1, GL_TRUE, (float*)&view);
		t_mat4 model = mat_identity();
		model = mat_translate(model, obj->trans);
		model = mat_rotate(model, VEC3(1, 0, 0), DEG_TO_RAD(obj->rot[0]));
		model = mat_rotate(model, VEC3(0, 1, 0), DEG_TO_RAD(obj->rot[1]));
		model = mat_rotate(model, VEC3(0, 0, 1), DEG_TO_RAD(obj->rot[2]));
		model = mat_scale(model, FLOAT_TO_VEC(g_object_scale));
		glUniformMatrix4fv(cam->uniform_model_loc, 1, GL_TRUE, (float*)&model);
		glUniform4fv(cam->uniform_light_loc, 1, (float*)&(cam->cam_pos));
		glUniform4fv(cam->uniform_obj_color, 1, (float*)&(obj->color));
		// glBindVertexArray(env->vao_floor);
		// glDrawArrays(GL_TRIANGLES, 0, obj->vertices_len);
		glBindVertexArray(env->vao_object);
		glDrawArrays(GL_TRIANGLES, 0, obj->vertices_len);
		uint32_t uniform_show_tex = glGetUniformLocation(env->shader_prog, "u_show_texture");
		if (obj->show_texture)
			glUniform1f(uniform_show_tex, 1.0f);
		else 
			glUniform1f(uniform_show_tex, 0.0f);
		glfwSwapBuffers(env->window);
		glfwPollEvents();
	}
}
