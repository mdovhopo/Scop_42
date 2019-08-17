/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_buffers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 22:37:24 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/17 16:39:37 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

// const float vertices[] = {
//     1.0f,  1.0f,  1.0f,     0.583f,  0.771f,  0.014f, // 0
//     1.0f,  1.0f, -1.0f,     0.609f,  0.115f,  0.436f, // 1
//     1.0f, -1.0f,  1.0f,     0.327f,  0.483f,  0.844f, // 2
//     1.0f, -1.0f, -1.0f,     0.822f,  0.569f,  0.201f, // 3
//    -1.0f,  1.0f,  1.0f,     0.435f,  0.602f,  0.223f, // 4
//    -1.0f,  1.0f, -1.0f,     0.310f,  0.747f,  0.185f, // 5
//    -1.0f, -1.0f,  1.0f,     0.597f,  0.770f,  0.761f, // 6
//    -1.0f, -1.0f, -1.0f,     0.559f,  0.436f,  0.730f, // 7

// };

// const uint32_t indices[] = {
//     0, 1, 2,
//     1, 2, 3,
//     4, 5, 6,
//     5, 6, 7,
//     2, 3, 7,
//     2, 7, 6,
//     0, 1, 4,
//     1, 4, 5,
//     0, 2, 4,
//     2, 4, 6,
//     1, 3, 5,
//     3, 5, 7
// };

void	init_buffers(t_obj *obj)
{
	uint32_t vao; // vertex_attrib_arr
	uint32_t ebo; // element_buffer_obj
	uint32_t vbo; // vertex_buffer_object
	uint32_t lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	// glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->vertices_len * sizeof(t_vertex), obj->vertices, GL_STATIC_DRAW);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj->indices_len * sizeof(t_veci3), obj->indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(t_vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(t_vertex), (void*)(sizeof(t_vec4)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}
