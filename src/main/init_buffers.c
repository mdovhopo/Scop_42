/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_buffers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 22:37:24 by tryckylake        #+#    #+#             */
/*   Updated: 2019/09/08 16:57:57 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_buffers_for_textures(t_obj *obj)
{
	if (obj->texture.data)
	{
		glGenTextures(1, &obj->texture.gl_text_id);
		glBindTexture(GL_TEXTURE_2D, obj->texture.gl_text_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
			obj->texture.width,
			obj->texture.height, 0,
			GL_RGB, GL_UNSIGNED_BYTE, obj->texture.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

void	init_buffers(t_obj *obj, t_gl_env *e)
{
	uint32_t vbo;
	uint32_t ebo;

	glGenVertexArrays(1, &(e->vao_object));
	glBindVertexArray(e->vao_object);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
	obj->vertices_len * sizeof(t_vertex), obj->vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(t_vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
					sizeof(t_vertex), (void*)(sizeof(t_vec4)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	init_buffers_for_textures(obj);
}
