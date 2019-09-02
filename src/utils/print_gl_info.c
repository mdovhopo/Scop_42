/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_gl_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 15:59:01 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/09/02 14:27:22 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	print_gl_info(void)
{
	ft_printf(CYN"System Info:\n");
	ft_printf("\tVENDOR: %s\n\tRENDERER: %s\n\tVERSION: %s\n\tGLSL %s\n"RESET,
		glGetString(GL_VENDOR),
		glGetString(GL_RENDERER),
		glGetString(GL_VERSION),
		glGetString(GL_SHADING_LANGUAGE_VERSION));
}
