/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_buffers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 22:37:24 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/23 17:28:28 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

const float vertices[] = {
    1.0f,  1.0f,  1.0f, 1.0f,
    1.0f,  1.0f, -1.0f, 1.0f,
    1.0f, -1.0f,  1.0f, 1.0f,
    1.0f, -1.0f, -1.0f, 1.0f,
   -1.0f,  1.0f,  1.0f, 1.0f,
   -1.0f,  1.0f, -1.0f, 1.0f,
   -1.0f, -1.0f,  1.0f, 1.0f,
   -1.0f, -1.0f, -1.0f, 1.0f,

};

const uint32_t indices[] = {
    0, 1, 2,
    1, 2, 3,
    4, 5, 6,
    5, 6, 7,
    2, 3, 7,
    2, 7, 6,
    0, 1, 4,
    1, 4, 5,
    0, 2, 4,
    2, 4, 6,
    1, 3, 5,
    3, 5, 7
};

void	init_buffers(t_obj *obj, t_gl_env *e)
{
	uint32_t vbo; // vertex_attrib_arr
	uint32_t ebo; // element_buffer_obj
	// uint32_t lightVAO;
	// glGenVertexArrays(1, &lightVAO);
	// glBindVertexArray(lightVAO);
	glGenVertexArrays(1, &(e->vao_object));
	glBindVertexArray(e->vao_object);

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);


	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->vertices_len * sizeof(t_vertex), obj->vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(t_vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(t_vertex), (void*)(sizeof(t_vec4)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	uint32_t vbo_2; // vertex_attrib_arr
	uint32_t ebo_2; // element_buffer_obj

	glGenVertexArrays(1, &(e->vao_floor));
	glBindVertexArray(e->vao_floor);

	glGenBuffers(1, &vbo_2);
	glGenBuffers(1, &ebo_2);


	glBindBuffer(GL_ARRAY_BUFFER, vbo_2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	// // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, szeof(t_vertex), (void*)(sizeof(t_vec4)));
	glEnableVertexAttribArray(0);
	// glEnableVertexAttribArray(1);
}
