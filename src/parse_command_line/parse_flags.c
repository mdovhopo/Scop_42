/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 16:21:39 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/08/25 17:49:00 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

const char	*g_flags_names[] = {
	"--help",
	"--file",
	"--window-name",
	"--color",
	"--window-size",
	NULL
};

t_handler_type	find_flag_id(char *flag_name)
{
	int i;

	i = -1;
	while (g_flags_names[++i])
	{
		if (ft_strequ(g_flags_names[i], flag_name))
			return (i);
	}
	return (UNKNOWN_FLAG);
}

void		(*g_flags_callbacks[])(t_gl_env *env, t_obj *obj, int *curr_arg, char *parm_name) = {
	&show_help,
	&get_file,
	&get_window_name,
	&get_color,
	&get_screen_size
};

static void	unknown_flag(char *flag_name)
{
	ft_printf(RED"ERROR: "RESET"Unexpected flag [%s]\n", flag_name);
	ft_printf("Checkout usage manual: --help\n");
	exit(1);
}

void		parse_flags(t_gl_env *env, t_obj *obj, int argc, char **argv)
{
	int				i;
	t_handler_type	type;

	if (argc == 1)
		g_flags_callbacks[SHOW_HELP](NULL, NULL, NULL, NULL);
	i = 0;
	obj->color = VEC(0.337254f, 0.396078f, 0.450980f, 1.0f);
	while (++i < argc)
	{
		type = find_flag_id(argv[i]);
		if (type == UNKNOWN_FLAG)
			unknown_flag(argv[i]);
		else
			g_flags_callbacks[type](env, obj, &i, argv[i + 1]);
	}
	if (!env->obj_file_name)
		exit(ft_printf(RED"ERROR: "RESET
			"You must specify obj file! (--help)\n"));
}
