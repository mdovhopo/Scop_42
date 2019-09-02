/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 14:27:08 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/09/02 14:27:11 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int32_t		gl_error_report(const char *msg, const int32_t exit_code)
{
	ft_printf("Error: [%s] exit with code %d", msg, exit_code);
	glfwTerminate();
	return (exit_code);
}
