/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 11:31:52 by tryckylake        #+#    #+#             */
/*   Updated: 2019/07/12 11:56:02 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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
    float cameraSpeed = 5.0f * delta_time; // adjust accordingly
	// TODO MacOS Clang cant multiply float and vector. Do smth with this 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam->cam_pos += VEC(cameraSpeed, cameraSpeed, cameraSpeed, cameraSpeed) * cam->cam_front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam->cam_pos -=  VEC(cameraSpeed, cameraSpeed, cameraSpeed, cameraSpeed) * cam->cam_front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam->cam_pos -= vec_unit(vec_cross(cam->cam_front, cam->cam_up)) *  VEC(cameraSpeed, cameraSpeed, cameraSpeed, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam->cam_pos += vec_unit(vec_cross(cam->cam_front, cam->cam_up)) *  VEC(cameraSpeed, cameraSpeed, cameraSpeed, cameraSpeed);
}

t_vec4 cube_pos[10] = {
  VEC( 0.0f,  0.0f,  0.0f, 0), 
  VEC( 2.0f,  5.0f, -15.0f, 0), 
  VEC(-1.5f, -2.2f, -2.5f, 0),  
  VEC(-3.8f, -2.0f, -12.3f, 0),  
  VEC( 2.4f, -0.4f, -3.5f, 0),  
  VEC(-1.7f,  3.0f, -7.5f, 0),  
  VEC( 1.3f, -2.0f, -2.5f, 0),  
  VEC( 1.5f,  2.0f, -2.5f, 0), 
  VEC( 1.5f,  0.2f, -1.5f, 0), 
  VEC(-1.3f,  1.0f, -1.5f, 0)
};

void	render_loop(t_gl_env *env, t_camera *cam)
{
	t_vec4 dir = {};

	while (!glfwWindowShouldClose(env->window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		get_delta_time();
		dir[0] = cos(DEG_TO_RAD(pitch)) * cos(DEG_TO_RAD(yaw));
		dir[1] = sin(DEG_TO_RAD(pitch));
		dir[2] = cos(DEG_TO_RAD(pitch)) * sin(DEG_TO_RAD(yaw));
		cam->cam_front = vec_unit(dir);
		t_mat4 view = mat_look_at(cam->cam_pos, cam->cam_pos + cam->cam_front, cam->cam_up);
		glUniformMatrix4fv(cam->uniform_view_loc, 1, GL_TRUE, (float*)&view);
		for (int i = 0; i < 10; i++) {
			t_mat4 model = mat_identity();
			model = mat_translate(model, cube_pos[i]);
			model = mat_rotate(model, VEC(1, 0.3f, 0.5f, 0), (float)glfwGetTime() * DEG_TO_RAD(30.0f * (i + 1)));
			glUniformMatrix4fv(cam->uniform_model_loc, 1, GL_TRUE, (float*)&model);
			glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
		}
		processInput(env->window, cam);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(env->window);
		glfwPollEvents();
	}
}
