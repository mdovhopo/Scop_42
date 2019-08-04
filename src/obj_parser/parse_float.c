/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:59:05 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/03 13:49:43 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int	get_sign(char *str, int *i)
{
	if (*str == '+')
	{
		*i += 1;
		return 1;
	}
	else if (*str == '-')
	{
		*i += 1;
		return -1;
	}
	return 1;
}

float		ft_parse_float(char *s, int *err)
{
	int		sign;
	char	*str;
	float	int_part;
	float	fraction;
	int		fraction_power;
	int		i;

	str = ft_strtrim(s);
	i = -1;
	while (ft_is_wspace(str[++i]))
		;
	if (str[i] == 0)
		return ft_printf(RED"ERROR"RESET" str is empty!"), 0;
	sign = get_sign(&str[i], &i);
	int_part = 0;
	fraction = 0;
	fraction_power = 0;
	while (ft_isdigit(str[i]))
	{
		int_part = str[i] - 48 + int_part * 10;
		i++;
	}
	if (str[i++] == '.')
	{
		while(ft_isdigit(str[i]))
		{
			fraction = str[i] - 48 + fraction * 10;
			fraction_power++;
			i++;
		}
	}
	if (str[i] == 0)
		*err = 0;
	else
		*err = 1;
	free(str);
	return (int_part + fraction * pow(10, -fraction_power)) * sign;
}
