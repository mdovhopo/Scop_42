/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:59:05 by tryckylake        #+#    #+#             */
/*   Updated: 2019/07/28 21:00:32 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int	get_sign(char **str)
{
	if (**str == '+')
	{
		*str += 1;
		return 1;
	}
	else if (**str == '-')
	{
		*str += 1;
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

	str = ft_strtrim(s);
	while (ft_is_wspace(*str))
		str += 1;
	if (*str == 0)
		return ft_printf(RED"ERROR"RESET" str is empty!"), 0;
	sign = get_sign(&str);
	int_part = 0;
	fraction = 0;
	fraction_power = 0;
	while (ft_isdigit(*str))
	{
		int_part = *str - 48 + int_part * 10;
		str++;
	}
	if (*str == '.')
	{
		str++;
		while(ft_isdigit(*str))
		{
			fraction = *str - 48 + fraction * 10;
			fraction_power++;
			str++;
		}
	}
	if (*str == 0)
		*err = 0;
	else
		*err = 1;
	return (int_part + fraction * pow(10, -fraction_power)) * sign;
}
