/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_index.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 11:58:00 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/04 18:13:12 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	parse_index(char** tokens, t_obj *obj, uint32_t line_count)
{
	t_veci3	v;
	int		length;
	int		err;
	int		i;

	length = -1;
	while(tokens[++length])
		;
	if (length < 3)
		throw_parsing_error(line_count, tokens[length],
			"Expected at least 3 integer values.");
	i = 1;
	while (++i < length)
	{
		v[0] = ft_parse_int(tokens[0], &err) - 1;
		if (err)
			throw_parsing_error(line_count, tokens[0], NULL);
		v[1] = ft_parse_int(tokens[i - 1], &err) - 1;
		if (err)
			throw_parsing_error(line_count, tokens[i - 1], NULL);
		v[2] = ft_parse_int(tokens[i], &err) - 1;
		if (err)
			throw_parsing_error(line_count, tokens[i], NULL);
		// printf("v[%d]\t%+f %+f %+f\n", i - 2, v[0], v[1], v[2]);
		obj->indices = ft_array_push(obj->indices, &v, sizeof(t_veci3), obj->indices_len++);
	}
}
