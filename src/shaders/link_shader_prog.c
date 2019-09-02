/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_shader_prog.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 14:21:38 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/09/02 14:22:55 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	link_shader_prog(uint32_t *prog_id, uint32_t *shaders, uint32_t length)
{
	int		success;
	int		index;
	char	info_log[512];

	index = length;
	*prog_id = glCreateProgram();
	while (--index > -1)
		glAttachShader(*prog_id, shaders[index]);
	glLinkProgram(*prog_id);
	glGetProgramiv(*prog_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(*prog_id, 512, NULL, info_log);
		ft_printf("PROGRAM LINK ERR: |%s|\n", info_log);
		return (false);
	}
	return (true);
}
