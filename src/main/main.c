/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 16:25:29 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/11/10 16:23:58 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define STB_IMAGE_IMPLEMENTATION
#include "scop.h"

void	clean_up(t_gl_env *env, t_obj *obj)
{
	glfwDestroyWindow(env->window);
	glfwTerminate();
	free(obj->points);
	free(obj->vertices);
	free(env->window_name);
	if (obj->texture.data)
		stbi_image_free(obj->texture.data);
}

int		main(int argc, char **argv)
{
	t_gl_env	env;
	t_camera	cam;
	t_obj		obj;

	ft_bzero(&env, sizeof(env));
	ft_bzero(&cam, sizeof(cam));
	ft_bzero(&obj, sizeof(obj));
	parse_flags(&env, &obj, argc, argv);
	ft_time_start();
	parse_obj_file(env.obj_file_name, &obj);
	ft_time_end("Parse time");
	if (!gl_env_init(&env))
		return (gl_error_report("OpenGL could not init :(", -1));
	init_buffers(&obj, &env);
	if (create_shader_prog(&(env.shader_prog)))
	{
		create_camera(&env, &cam, &obj);
		load_camera_projection(&cam, 45.0f, VEC2(0.1f, 10000.0f));
		if (glGetError() != GL_NO_ERROR)
			ft_printf("WARNING glError: %d", glGetError());
		render_loop(&env, &cam, &obj);
	}
	clean_up(&env, &obj);
	system("leaks -q sco");
	return (0);
}
