/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 14:46:02 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/09/02 14:10:35 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** TODO test this
*/

static t_vec4	hex_color_to_vec4(const char *hex_color)
{
	int					i;
	t_vec4				res;
	static const char	*hex_chars = "abcdefABCDEF";

	i = -1;
	res = VEC(0.0f, 0.0f, 0.0f, 1.0f);
	while (hex_color[++i])
	{
		if (!ft_isdigit(hex_color[i]) && !ft_strchr(hex_chars, hex_color[i]))
			exit(ft_printf(RED"ERROR: "RESET
				"Unexpected symbol [%c]. (--help)\n", hex_color[i]));
		if ((i + 1) % 2 == 0)
		{
			res[(i) / 2] += ft_isdigit(hex_color[i])
				? hex_color[i] - 48
				: ft_toupper(hex_color[i]) - 55;
			res[(i) / 2] += (ft_isdigit(hex_color[i - 1])
				? hex_color[i - 1] - 48
				: ft_toupper(hex_color[i - 1]) - 55) * 16;
			res[(i) / 2] /= 255;
		}
	}
	return (res);
}

void			get_color(t_gl_env *env, t_obj *obj,
										int *curr_arg, char *param_name)
{
	char *trimmed_name;

	trimmed_name = ft_strtrim(param_name);
	*curr_arg += 1;
	if (trimmed_name == NULL)
		exit(ft_printf(RED"ERROR: "RESET
		"You must specify color. "
		"Also you can try wrap color like this: \"#424242\" (--help)\n"));
	if (trimmed_name[0] != '#' || ft_strlen(trimmed_name + 1) != 6)
		exit(ft_printf(RED"ERROR: "RESET
						"Color must be in hex format: #ff00ff (--help)\n"));
	obj->color = hex_color_to_vec4(trimmed_name + 1);
}
