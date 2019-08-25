/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_screen_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 16:19:51 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/08/25 17:26:44 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool	str_is_num(const char *str)
{
	int i;

	if (!str)
		return (false);
	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (false);
	return (true);
}

static void	set_dimention(uint32_t *size, char *str_size)
{
	int	int_size;

	int_size = ft_atoi(str_size);
	if (str_is_num(str_size) && int_size > 299 && int_size < 6001)
		*size = int_size;
	else
		ft_printf(YEL"WARNING: "RESET
			"Size must be an integer from 300 to 6000, set to fullscreen. (--help)\n");
}

void		get_screen_size(t_gl_env *env, t_obj *obj, int *curr_arg, char *param_name)
{
	char	*param;
	char	**sizes;
	int		i;

	param = ft_strtrim(param_name);
	*curr_arg += 1;
	if (!param)
		exit(ft_printf(RED"ERROR: "RESET
			"You must specify screen size in format: 800x600. (--help)\n"));
	sizes = ft_strsplit(param, 'x');
	i = -1;
	while (sizes[++i])
		if (i > 1)
			exit(ft_printf(RED"ERROR: "RESET
				"You must specify screen size in format: 800x600. (--help)\n"));
	set_dimention(&(env->w_width), sizes[0]);
	set_dimention(&(env->w_height), sizes[1]);
	free(param);
	free_2d_arr(sizes);
}
