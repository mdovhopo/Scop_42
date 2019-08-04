/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 11:52:14 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/03 11:52:46 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	throw_parsing_error(uint32_t line_count, char *token, char *msg)
{
	ft_printf(RED"Parsing Error: "RESET
			"line:%d Unexpected token: %s\n", line_count, token);
	if (msg)
		ft_printf(YEL"\n%s\n"RESET, msg);
	ft_printf(GRN"\nLearn more about .obj format:\n"RESET
			BLU"https://en.wikipedia.org/wiki/Wavefront_.obj_file\n"RESET);
	exit(-1);
}
