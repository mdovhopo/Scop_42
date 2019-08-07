/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getDeltaTime.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 11:41:32 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/07 14:52:56 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	get_delta_time(void)
{
	static float current_frame = 0;
	static float last_frame = 0;

	current_frame = glfwGetTime();
	delta_time = current_frame - last_frame;
	last_frame = current_frame;
}
