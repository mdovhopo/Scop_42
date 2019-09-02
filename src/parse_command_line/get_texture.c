/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:18:00 by mdovhopo          #+#    #+#             */
/*   Updated: 2019/09/02 14:15:24 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	get_texture(t_gl_env *env, t_obj *obj,
									int *curr_arg, char *parm_name)
{
	size_t	name_len;
	int		nr_channels;

	*curr_arg += 1;
	if (!parm_name)
		exit(ft_printf(RED"ERROR: "RESET
				"You must specify file name. (--help)\n"));
	if ((name_len = ft_strlen(parm_name)) > 255)
		exit(ft_printf(RED"ERROR: "RESET
						"Filename is too long (255 max). (--help)\n"));
	if (name_len < 5 || ft_strcmp(".jpg", parm_name + name_len - 4))
		exit(ft_printf(RED"ERROR: "RESET
						"File must be .jpg . (--help)\n"));
	if (obj->texture.data)
		stbi_image_free(obj->texture.data);
	obj->texture.data = stbi_load(parm_name, &(obj->texture.width),
		&(obj->texture.height), &nr_channels, 0);
	if (!obj->texture.data)
		ft_printf(YEL"WARNING: texture %s couldn't load\n"RESET, parm_name);
	else
	{
		obj->show_texture = true;
		ft_printf(GRN"Texture %s loaded!\n\n", parm_name);
	}
}
