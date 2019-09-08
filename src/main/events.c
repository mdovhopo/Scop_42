/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:15:18 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/09/08 17:18:18 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		handle_trans_obj(t_obj *obj, GLFWwindow *window, float cam_vel)
{
	float camera_speed;

	camera_speed = cam_vel * g_dt;
	if (obj->manage_type == OBJ_ROTATE)
	{
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			obj->rot[0] = loop(-180.0f, 180.0f, obj->rot[0] + 100.0f * g_dt);
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			obj->rot[0] = loop(-180.0f, 180.0f, obj->rot[0] - 100.0f * g_dt);
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			obj->rot[1] = loop(-180.0f, 180.0f, obj->rot[1] + 100.0f * g_dt);
		else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			obj->rot[1] = loop(-180.0f, 180.0f, obj->rot[1] - 100.0f * g_dt);
		if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
			obj->rot[2] = loop(-180.0f, 180.0f, obj->rot[2] + 100.0f * g_dt);
		else if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
			obj->rot[2] = loop(-180.0f, 180.0f, obj->rot[2] - 100.0f * g_dt);
	}
}

static void		handle_rot_obj(t_obj *obj, GLFWwindow *window, float cam_speed)
{
	float camera_speed;

	camera_speed = cam_speed * g_dt;
	if (obj->manage_type == OBJ_TRANSLATE)
	{
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			obj->trans[0] = obj->trans[0] + camera_speed;
		else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			obj->trans[0] = obj->trans[0] - camera_speed;
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			obj->trans[1] = obj->trans[1] + camera_speed;
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			obj->trans[1] = obj->trans[1] - camera_speed;
		if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
			obj->trans[2] = obj->trans[2] + camera_speed;
		else if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
			obj->trans[2] = obj->trans[2] - camera_speed;
	}
}

static void		reset_scene(t_obj *obj, t_camera *cam)
{
	obj->rot = VEC3(0, 0, 0);
	obj->trans = VEC3(0, 0, 0);
	cam->cam_pos = VEC3(
		cam->cam_rotate_radius * 2,
		cam->cam_rotate_radius * 5,
		(int32_t)cam->cam_rotate_radius * -2);
	g_object_scale = 1.0f;
	g_pitch = 0.0f;
	g_yaw = -90.0f;
}

static void		set_texture_visibility(t_obj *obj, GLFWwindow *window)
{
	static bool	key_pressed = false;

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS
								&& key_pressed == false)
	{
		obj->show_texture = !obj->show_texture;
		key_pressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE
								&& key_pressed == true)
		key_pressed = false;
}

void			process_input(GLFWwindow *window, t_camera *cam, t_obj *obj)
{
	set_texture_visibility(obj, window);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		obj->manage_type = 1;
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		obj->manage_type = 0;
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		reset_scene(obj, cam);
	handle_trans_obj(obj, window, cam->cam_speed);
	handle_rot_obj(obj, window, cam->cam_speed);
}
