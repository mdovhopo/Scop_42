/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 16:25:29 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/09/01 13:18:16 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define STB_IMAGE_IMPLEMENTATION
#include "scop.h"

void	dump_parced_object(t_obj obj, bool debug)
{
	printf("[Dump Points array of length %d]\n", obj.points_len);
	if (debug) {
		for (int i = 0; i < obj.points_len; i++) {
			printf("v[%d]\t%+f %+f %+f\n", i, obj.points[i][0], obj.points[i][1], obj.points[i][2]);
		}
	}
	printf("[Dump Normals array of length %d]\n", obj.normals_len);
	if (debug) {
		for (int i = 0; i < obj.normals_len; i++) {
			printf("f[%d]\t%f %f %f\n", i, obj.normals[i][0], obj.normals[i][1], obj.normals[i][2]);
		}
	}
	printf("[Dump Vertex array of length %d]\n", obj.vertices_len);
	if (debug) {
		for (int i = 0; i < obj.vertices_len; i++) {
			t_vec4 p = obj.vertices[i].point;
			t_vec4 n = obj.vertices[i].normal;
			printf("v [%d]\t%+f %+f %+f\n", i, p[0], p[1], p[2]);
			printf("vn[%d]\t%+f +%f %+f\n", i, n[0], n[1], n[2]);
		}
	}
}



int main(int argc, char **argv)
{
	t_gl_env	env = {};
	t_camera	cam = {};
	t_obj		obj = {};

	parse_flags(&env, &obj, argc, argv);
	ft_time_start();
	parse_obj_file(env.obj_file_name, &obj);
	ft_time_end("Parse time");
	dump_parced_object(obj, false);
	if (!gl_env_init(&env))
		return (gl_error_report("OpenGL could not init :(", -1));
	print_gl_info();

	int width, height, nrChannels;
	unsigned char *data = stbi_load("./assets/wall.jpg", &width, &height, &nrChannels, 0); 
	if (data)  {
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    	glGenerateMipmap(GL_TEXTURE_2D);
		printf(GRN"loaded\n"RESET);
	}
	else printf("not loaded\n");
	// return 0;

	init_buffers(&obj, &env);
	if (create_shader_prog(&(env.shader_prog)))
	{
		create_camera(&env, &cam, &obj);
		load_camera_projection(&cam, 45.0f, CAMERA_PERSPECTIVE, VEC2(0.1f, 10000.0f));

		if (glGetError() != GL_NO_ERROR)
			ft_printf("WARNING glError: %d", glGetError());

		render_loop(&env, &cam, &obj);
	}
	glfwDestroyWindow(env.window);
	glfwTerminate();
	free(obj.points);
	free(obj.vertices);
	free(env.window_name);
	stbi_image_free(data);
	return (0);
}
