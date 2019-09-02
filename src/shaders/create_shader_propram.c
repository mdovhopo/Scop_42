/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_shader_propram.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 21:29:20 by tryckylake        #+#    #+#             */
/*   Updated: 2019/09/02 14:26:04 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	create_shader_prog(uint32_t *prog)
{
	char		*vert_shader_src;
	char		*frag_shader_src;
	uint32_t	vart_shader_id;
	uint32_t	frag_shader_id;
	uint32_t	shader_prog;

	frag_shader_src = ft_read_file(FRAGMENT_SHADER_PATH);
	vert_shader_src = ft_read_file(VERTEX_SHADER_PATH);
	if (!compile_shader(&vart_shader_id, vert_shader_src,
									GL_VERTEX_SHADER, VERTEX_SHADER_PATH))
		return (false);
	if (!compile_shader(&frag_shader_id, frag_shader_src,
									GL_FRAGMENT_SHADER, FRAGMENT_SHADER_PATH))
		return (false);
	free(vert_shader_src);
	free(frag_shader_src);
	if (!link_shader_prog(&shader_prog,
						(uint32_t[]){vart_shader_id, frag_shader_id}, 2))
		return (false);
	glDeleteShader(vart_shader_id);
	glDeleteShader(frag_shader_id);
	glUseProgram(shader_prog);
	*prog = shader_prog;
	return (true);
}
