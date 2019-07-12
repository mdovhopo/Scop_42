/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getDeltaTime.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 11:41:32 by tryckylake        #+#    #+#             */
/*   Updated: 2019/07/12 11:53:45 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"


void	get_delta_time(void)
{
	float current_frame;

	current_frame = glfwGetTime();
	delta_time = current_frame - last_frame;
	last_frame = current_frame;
}
