/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_index.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 11:58:00 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/05 14:50:01 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	parse_index(char** tokens, t_obj *obj, uint32_t line_count)
{
	t_veci3	v;
	int		length;
	int		err;
	int		i;
	char	**index_data;

	length = -1;
	while(tokens[++length])
		;
	if (length < 3)
		throw_parsing_error(line_count, tokens[length],
			"Expected at least 3 integer values.");
	i = 1;
	while (++i < length)
	{
		// TODO error handle stuff for 1/1/1 format
		index_data = ft_strsplit(tokens[0], '/');
		v[0] = ft_parse_int(index_data[0], &err) - 1;
		free_2d_arr(index_data);
		if (err)
			throw_parsing_error(line_count, tokens[0], NULL);
		//**********************
		index_data = ft_strsplit(tokens[i - 1], '/');
		v[1] = ft_parse_int( index_data[0], &err) - 1;
		free_2d_arr(index_data);
		if (err)
			throw_parsing_error(line_count, tokens[i - 1], NULL);
		//********************
		index_data = ft_strsplit(tokens[i], '/');
		v[2] = ft_parse_int(index_data[0], &err) - 1;
		free_2d_arr(index_data);
		if (err)
			throw_parsing_error(line_count, tokens[i], NULL);
		// printf("v[%d]\t%+f %+f %+f\n", i - 2, v[0], v[1], v[2]);
		obj->indices = ft_array_push(obj->indices, &v, sizeof(t_veci3), obj->indices_len++);
	}
}
