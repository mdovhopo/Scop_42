/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vertex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 11:57:37 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/17 16:25:16 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	parse_vertex(char** tokens, t_obj *obj, uint32_t line_count)
{
	t_vec4	v;
	int		i;
	int		err;

	v = VEC3(0.0f, 0.0f, 0.0f);
	i = -1;
	while (tokens[++i])
	{
		v[i] = ft_parse_float(tokens[i], &err);
		if (err)
			throw_parsing_error(line_count, tokens[i], NULL);
		if (i > 3)
			throw_parsing_error(line_count, tokens[i],
				"Expected no more then 4 float values");
	}
	if (i < 3)
		throw_parsing_error(line_count, tokens[i], 
				"Expected at least 3 float values");
	if (vec_mag(obj->farest_point) < vec_mag(v))
		obj->farest_point = v;
	obj->points = ft_array_push(obj->points, &v, sizeof(t_vec4), obj->points_len++);
}
