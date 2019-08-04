/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 12:06:11 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/03 13:18:44 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int32_t	find_str_in_array(char** arr, char* to_find)
{
	int32_t i = 0;
	while (*arr != NULL)
	{
		if (ft_strequ(*arr, to_find) == 1)
			return (i);
		i++;
		arr++;
	}
	return (-1);
}

void	free_2d_arr(char **arr)
{
	char *tmp;
	char **to_free;

	to_free = arr;
	while (*to_free)
	{
		tmp = *to_free;
		to_free++;
		free(tmp);
	}
	free(arr);
}
