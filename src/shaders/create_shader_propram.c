/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_shader_propram.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 21:29:20 by tryckylake        #+#    #+#             */
/*   Updated: 2019/07/11 21:56:39 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool	create_shader_prog(uint32_t *prog)
{
	char		*vertShaderCode;
	char		*fragShaderCode;
	uint32_t	vertShaderId;
	uint32_t	fragShaderId;
	uint32_t	shaderProg;
	fragShaderCode = ft_read_file(FRAGMENT_SHADER_PATH);
	vertShaderCode = ft_read_file(VERTEX_SHADER_PATH);

	// Compile shaders
	if(!compile_shader(&vertShaderId, vertShaderCode, GL_VERTEX_SHADER, VERTEX_SHADER_PATH))
		return (false);
	if (!compile_shader(&fragShaderId, fragShaderCode, GL_FRAGMENT_SHADER, FRAGMENT_SHADER_PATH))
		return (false);
	free(vertShaderCode);
	free(fragShaderCode);
	// Link Program
	if (!link_shader_prog(&shaderProg, (uint32_t[]){vertShaderId, fragShaderId}, 2))
		return (false);
	glDeleteShader(vertShaderId);
	glDeleteShader(fragShaderId);  
	glUseProgram(shaderProg);
	*prog = shaderProg;
	return (true);
}
