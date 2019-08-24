/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 17:01:43 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/08/24 17:28:15 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	show_help(t_gl_env *env, t_obj *obj, int *curr_arg, char *parm_name) 
{
	ft_printf("\t###############################\n");
	ft_printf("\t####         Scop          ####\n");
	ft_printf("\t###############################\n");
	ft_printf("\t         Usage manual\n\n");
	ft_printf("\t--help - show help(usage manual)\n");
	ft_printf("\t--file <file> - specify file with model to render."
										"Must be valid *.obj file\n");
	ft_printf("\t--window-name <name> - specify window name\n");
	exit(1);
}
