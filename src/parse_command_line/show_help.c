/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 17:01:43 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/11/10 15:31:22 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	show_help(t_gl_env *env, t_obj *obj, int *curr_arg, char *parm_name)
{
	(void)env;
	(void)obj;
	(void)curr_arg;
	(void)parm_name;
	ft_printf(BLU"\t###############################\n"
	"\t####         Scop          ####\n"
	"\t###############################\n"
	"\t         Usage manual\n\n"
	"\t--help - show help(usage manual)\n"
	"\t--file <file> - specify file with model to render."
										"Must be valid *.obj file\n"
	"\t--color <hex color code>"
	" - specify color for object (#ff00ff)\n"
	"\t--texture <texture name> - specify a texture for object\n"
	"\t--window-name <name> - specify window name\n"
	"\t--window-size <width>x<height>"
	" - specify screen size (1600x900)\n"RESET);
	exit(1);
}
