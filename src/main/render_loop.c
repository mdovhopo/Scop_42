/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 11:31:52 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/07 14:32:33 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

const uint32_t	cam_rotate_radius = 100;

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
	float cameraSpeed = cam->cam_speed * delta_time; // adjust accordingly
	// TODO MacOS Clang cant multiply float and vector. Do smth with this 
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		obj->rot = VEC3(0, 0, 0);
		obj->trans = VEC3(0, 0, 0);
		cam->cam_pos = VEC3(
			0, 
			fabsf(obj->farest_point[1]) / 2, 
			(fabsf(obj->farest_point[2]) + fabsf(obj->farest_point[0])) * 2
		);
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
			obj->rot[0] = clamp(-180.0f, 180.0f, obj->rot[0] + 100.0f * delta_time);
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			obj->rot[0] = clamp(-180.0f, 180.0f, obj->rot[0] - 100.0f * delta_time);
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			obj->rot[1] = clamp(-180.0f, 180.0f, obj->rot[1] + 100.0f * delta_time);
		else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			obj->rot[1] = clamp(-180.0f, 180.0f, obj->rot[1] - 100.0f * delta_time);
		if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
			obj->rot[2] = clamp(-180.0f, 180.0f, obj->rot[2] + 100.0f * delta_time);
		else if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
			obj->rot[2] = clamp(-180.0f, 180.0f, obj->rot[2] - 100.0f * delta_time);
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
		cam->cam_front = vec_unit(dir);
		t_mat4 view = mat_look_at(cam->cam_pos, cam->cam_pos + cam->cam_front, cam->cam_up);
		glUniformMatrix4fv(cam->uniform_view_loc, 1, GL_TRUE, (float*)&view);
		t_mat4 model = mat_identity();
		model = mat_translate(model, obj->trans);
		model = mat_rotate(model, VEC3(1, 0, 0), DEG_TO_RAD(obj->rot[0]));
		model = mat_rotate(model, VEC3(0, 1, 0), DEG_TO_RAD(obj->rot[1]));
		model = mat_rotate(model, VEC3(0, 0, 1), DEG_TO_RAD(obj->rot[2]));
		glUniformMatrix4fv(cam->uniform_model_loc, 1, GL_TRUE, (float*)&model);
		glDrawElements(GL_TRIANGLES, obj->indices_len * 3, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(env->window);
		glfwPollEvents();
	}
}
