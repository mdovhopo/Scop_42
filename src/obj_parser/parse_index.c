/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_index.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 11:58:00 by tryckylake        #+#    #+#             */
/*   Updated: 2019/09/08 16:32:42 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	set_normals(t_obj *obj, t_vertex *vrt)
{
	if (obj->vertices_len && (obj->vertices_len + 1) % 3 == 0)
	{
		vrt->normal = ft_get_triangle_normal(
			obj->vertices[obj->vertices_len - 2].point,
			obj->vertices[obj->vertices_len - 1].point,
			vrt->point);
		obj->vertices[obj->vertices_len - 2].normal = vrt->normal;
		obj->vertices[obj->vertices_len - 1].normal = vrt->normal;
	}
}

static void	pack_vertex(char **tokens, t_obj *obj, uint32_t line_count, int i)
{
	int32_t		j;
	int32_t		err;
	char		**index_data;
	uint32_t	index;
	t_vertex	vrt;

	j = 3;
	while (--j > -1)
	{
		index = j == 2 ? 0 : i - j;
		index_data = ft_strsplit(tokens[index], '/');
		vrt.point = obj->points[ft_parse_int(index_data[0], &err) - 1];
		if (index_data[1] && index_data[1][0] == '\0')
			ft_printf(YEL"WARNING no normal");
		set_normals(obj, &vrt);
		obj->vertices = ft_array_push(obj->vertices, &vrt,
										sizeof(t_vertex), obj->vertices_len++);
		free_2d_arr(index_data);
		if (err)
			throw_parsing_error(line_count, tokens[index], NULL);
	}
}

void		parse_index(char **tokens, t_obj *obj, uint32_t line_count)
{
	int		length;
	int		i;

	length = -1;
	while (tokens[++length])
		;
	if (length < 3)
		throw_parsing_error(line_count, tokens[length],
			"Expected at least 3 integer values.");
	i = 1;
	while (++i < length)
		pack_vertex(tokens, obj, line_count, i);
}
