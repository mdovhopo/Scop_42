/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 11:31:52 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/25 15:14:14 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void processInput(GLFWwindow *window, t_camera *cam, t_obj *obj)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	float cameraSpeed = cam->cam_speed * delta_time;
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		obj->rot = VEC3(0, 0, 0);
		obj->trans = VEC3(0, 0, 0);
		cam->cam_pos = VEC3(
			cam->cam_rotate_radius * 2, 
			cam->cam_rotate_radius * 5, 
			(int32_t)cam->cam_rotate_radius * -2
		);
		object_scale = 1.0f;
		pitch = 0.0f;
		yaw = -90.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		obj->manage_type = 0;
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		obj->manage_type = 1;
	if (obj->manage_type == OBJ_ROTATE)
	{
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			obj->rot[0] = loop(-180.0f, 180.0f, obj->rot[0] + 100.0f * delta_time);
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			obj->rot[0] = loop(-180.0f, 180.0f, obj->rot[0] - 100.0f * delta_time);
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			obj->rot[1] = loop(-180.0f, 180.0f, obj->rot[1] + 100.0f * delta_time);
		else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			obj->rot[1] = loop(-180.0f, 180.0f, obj->rot[1] - 100.0f * delta_time);
		if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
			obj->rot[2] = loop(-180.0f, 180.0f, obj->rot[2] + 100.0f * delta_time);
		else if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
			obj->rot[2] = loop(-180.0f, 180.0f, obj->rot[2] - 100.0f * delta_time);
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
	// Camera movement need to be locket by default
	return;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam->cam_pos += VEC(cameraSpeed, cameraSpeed, cameraSpeed, cameraSpeed) * cam->cam_front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam->cam_pos -=  VEC(cameraSpeed, cameraSpeed, cameraSpeed, cameraSpeed) * cam->cam_front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam->cam_pos -= vec_unit(vec_cross(cam->cam_front, cam->cam_up)) *  VEC(cameraSpeed, cameraSpeed, cameraSpeed, cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam->cam_pos += vec_unit(vec_cross(cam->cam_front, cam->cam_up)) *  VEC(cameraSpeed, cameraSpeed, cameraSpeed, cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		cam->cam_pos -= cam->cam_up * VEC(cameraSpeed, cameraSpeed, cameraSpeed, cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		cam->cam_pos += cam->cam_up * VEC(cameraSpeed, cameraSpeed, cameraSpeed, cameraSpeed);
}

t_vec4 cube_pos[] = {
	VEC(0, 0, 0, 0.5),
	VEC(3, 3, -1, 0.2),
	VEC(-3, 3, -1, 0.2),
	VEC(0, -3, -1, 0.2)
};

void	render_loop(t_gl_env *env, t_camera *cam, t_obj *obj)
{
	t_vec4 dir = {};

	while (!glfwWindowShouldClose(env->window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		get_delta_time();
		processInput(env->window, cam, obj);
		dir[0] = cos(DEG_TO_RAD(pitch)) * cos(DEG_TO_RAD(yaw));
		dir[1] = sin(DEG_TO_RAD(pitch));
		dir[2] = cos(DEG_TO_RAD(pitch)) * sin(DEG_TO_RAD(yaw));
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
		model = mat_scale(model, FLOAT_TO_VEC(object_scale));
		glUniformMatrix4fv(cam->uniform_model_loc, 1, GL_TRUE, (float*)&model);
		glUniform4fv(cam->uniform_light_loc, 1, (float*)&(cam->cam_pos));
		glUniform4fv(cam->uniform_obj_color, 1, (float*)&(obj->color));
		glBindVertexArray(env->vao_object);
		glDrawArrays(GL_TRIANGLES, 0, obj->vertices_len);
		// glBindVertexArray(env->vao_floor);
		// glDrawArrays(GL_TRIANGLES, 0, obj->vertices_len);
		glfwSwapBuffers(env->window);
		glfwPollEvents();
	}
}
