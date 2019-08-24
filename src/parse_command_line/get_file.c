/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 17:06:41 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/08/24 18:00:28 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	get_file(t_gl_env *env, t_obj *obj, int *curr_arg, char *parm_name)
{
	size_t	name_len;

	*curr_arg += 1;

	if (parm_name == NULL)
		exit(ft_printf(RED"ERROR: "RESET
						"You must specify file name. (--help)\n"));
	if ((name_len = ft_strlen(parm_name)) > 255)
		exit(ft_printf(RED"ERROR: "RESET
						"Filename is too long (255 max). (--help)\n"));
	if (name_len < 5 || ft_strcmp(".obj", parm_name + name_len - 4)) 
		exit(ft_printf(RED"ERROR: "RESET
						"File must be .obj . (--help)\n"));
	env->obj_file_name = parm_name;
	env->window_name = parm_name;
}
