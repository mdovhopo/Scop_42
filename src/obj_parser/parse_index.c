/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_index.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 11:58:00 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/21 16:55:51 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	pack_vertex(char **tokens, t_obj *obj, uint32_t line_count, int i)
{
	int32_t		j = 3;
	int32_t		err;
	char		**index_data;
	uint32_t	index;

	while (--j > -1)
	{
		index = j == 2 ? 0 : i - j;
		index_data = ft_strsplit(tokens[index], '/');
		t_vertex	vrt = {};
		int v_index = ft_parse_int(index_data[0], &err) - 1;
		vrt.point = obj->points[v_index];
		if (index_data[1] && index_data[1][0] == '\0') printf(YEL"WARNING no normal");
		if (index_data[1] == NULL) {
			if ((obj->vertices_len + 2) % 3 == 0) {
				vrt.normal = ft_get_triangle_normal((t_vec4[]){
					obj->vertices[obj->vertices_len - 1].point,
					obj->vertices[obj->vertices_len].point,
					vrt.point
				});
			}
		} else {
			int vn_index = ft_parse_int(index_data[1], &err) - 1;
			vrt.normal = obj->normals[vn_index];
		}
		obj->vertices = ft_array_push(obj->vertices, &vrt, sizeof(t_vertex), obj->vertices_len++);
		free_2d_arr(index_data);
		if (err)
			throw_parsing_error(line_count, tokens[index], NULL);
	}
}

void		parse_index(char** tokens, t_obj *obj, uint32_t line_count)
{
	int		length;
	int		i;

	length = -1;
	while(tokens[++length])
		;
	if (length < 3)
		throw_parsing_error(line_count, tokens[length],
			"Expected at least 3 integer values.");
	i = 1;
	while (++i < length)
		pack_vertex(tokens, obj, line_count, i);
}
