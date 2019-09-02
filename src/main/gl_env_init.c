/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:48:44 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/09/02 14:51:05 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

float	g_object_scale = 1.0f;

void	scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	if (yoffset)
	{
		if (yoffset < 0)
			g_object_scale = clamp(0.1f, 100.0f, g_object_scale += 0.1f);
		else
			g_object_scale = clamp(0.1f, 100.0f, g_object_scale -= 0.1f);
	}
}

float	g_yaw = -90.0f;
float	g_pitch = 0;
float	g_last_x = 400;
float	g_last_y = 300;

float	g_delta_time = 0.0f;

bool	g_first_mouse = true;

void	mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	float xoffset;
	float yoffset;

	if (g_first_mouse)
	{
		g_last_x = xpos;
		g_last_y = ypos;
		g_first_mouse = false;
	}
	xoffset = xpos - g_last_x;
	yoffset = g_last_y - ypos;
	g_last_x = xpos;
	g_last_y = ypos;
	xoffset *= MOUSE_SENSITIVITY;
	yoffset *= MOUSE_SENSITIVITY;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		g_yaw += xoffset;
		g_pitch -= yoffset;
		g_pitch = clamp(-89.0f, 89.0f, g_pitch);
	}
}

bool	init_window(t_gl_env *e)
{
	GLFWmonitor			*monitor;
	const GLFWvidmode	*mode;

	monitor = NULL;
	if (e->w_width == 0 || e->w_height == 0)
	{
		monitor = glfwGetPrimaryMonitor();
		mode = glfwGetVideoMode(monitor);
		e->w_width = mode->width;
		e->w_height = mode->height;
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		e->window = glfwCreateWindow(e->w_width,
				e->w_height, e->window_name, monitor, NULL);
		glfwSetWindowMonitor(e->window, monitor, 0, 0,
				e->w_width, e->w_height, mode->refreshRate);
	}
	else
		e->window = glfwCreateWindow(e->w_width,
				e->w_height, e->window_name, NULL, NULL);
	if (!(e->window))
		return (false);
	return (true);
}

bool	gl_env_init(t_gl_env *e)
{
	if (!glfwInit())
		return (false);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (!(init_window(e)))
		return (gl_error_report("Could not create window :(", 0));
	glfwGetFramebufferSize(e->window, (int*)&e->w_width, (int*)&e->w_height);
	glfwMakeContextCurrent(e->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return (gl_error_report("Could not load GL functions :(", 0));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, e->w_width, e->w_height);
	glfwSetInputMode(e->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(e->window, scroll_callback);
	glfwSetCursorPosCallback(e->window, mouse_callback);
	print_gl_info();
	return (true);
}
