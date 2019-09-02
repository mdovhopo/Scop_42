/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_window_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 17:39:54 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/09/02 14:10:57 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	get_window_name(t_gl_env *env, t_obj *obj,
										int *curr_arg, char *parm_name)
{
	char *trimmed_name;

	trimmed_name = ft_strtrim(parm_name);
	*curr_arg += 1;
	if (trimmed_name[0] == '\0')
		exit(ft_printf(RED"ERROR: "RESET
						"Window name can't be an empty. (--help)\n"));
	if (trimmed_name == NULL)
		exit(ft_printf(RED"ERROR: "RESET
						"You must specify window name. (--help)\n"));
	if (ft_strlen(trimmed_name) > 42)
		exit(ft_printf(RED"ERROR: "RESET
						"Filename is too long (42 max). (--help)\n"));
	env->window_name = trimmed_name;
}
