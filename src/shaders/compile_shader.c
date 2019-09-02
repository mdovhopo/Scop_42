/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_shader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 14:18:07 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/09/02 14:22:25 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	compile_shader(uint32_t *shader_id, const char *source,
										int32_t type, const char *name)
{
	int		success;
	char	info_log[512];

	*shader_id = glCreateShader(type);
	glShaderSource(*shader_id, 1, (const char *const *)&source, NULL);
	glCompileShader(*shader_id);
	glGetShaderiv(*shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*shader_id, 512, NULL, info_log);
		ft_printf("in %s: %s", name, info_log);
		return (false);
	}
	return (true);
}
