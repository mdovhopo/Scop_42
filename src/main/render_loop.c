/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 11:31:52 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/06 12:51:45 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <time.h>

clock_t start;

static void	time_start()
{
	start = clock();
}

static void	time_end(const char *name)
{
	double cpu_time_used;
	clock_t end;
	end = clock();
	cpu_time_used = ((double) (end - start));
	printf("%s: [%fms]\n", name, cpu_time_used); 
}

void processInput(GLFWwindow *window, t_camera *cam)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	float cameraSpeed = 50.0f * delta_time; // adjust accordingly
	// TODO MacOS Clang cant multiply float and vector. Do smth with this 
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
		time_start();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		get_delta_time();
		processInput(env->window, cam);
		dir[0] = cos(DEG_TO_RAD(pitch)) * cos(DEG_TO_RAD(yaw));
		dir[1] = sin(DEG_TO_RAD(pitch));
		dir[2] = cos(DEG_TO_RAD(pitch)) * sin(DEG_TO_RAD(yaw));
		cam->cam_front = vec_unit(dir);
		t_mat4 view = mat_look_at(cam->cam_pos, cam->cam_pos + cam->cam_front, cam->cam_up);
		glUniformMatrix4fv(cam->uniform_view_loc, 1, GL_TRUE, (float*)&view);
		t_mat4 model = mat_identity();
		model = mat_translate(model, VEC(0, -25, -200, 0));
		// model = mat_rotate(model, VEC(1, 0.3f, 0.5f, 0), (float)glfwGetTime() * DEG_TO_RAD(30.0f));
		glUniformMatrix4fv(cam->uniform_model_loc, 1, GL_TRUE, (float*)&model);
		glDrawElements(GL_TRIANGLES, obj->indices_len * 3, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(env->window);
		glfwPollEvents();
		time_end("Render Time:");
	}
}
