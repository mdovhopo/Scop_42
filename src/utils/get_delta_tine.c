/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_delta_tine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 11:41:32 by tryckylake        #+#    #+#             */
/*   Updated: 2019/09/08 17:06:21 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	get_delta_time(void)
{
	static float current_frame = 0;
	static float last_frame = 0;

	current_frame = glfwGetTime();
	g_dt = current_frame - last_frame;
	last_frame = current_frame;
}
