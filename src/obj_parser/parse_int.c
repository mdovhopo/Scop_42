/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 02:06:41 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/03 02:11:24 by tryckylake       ###   ########.fr       */
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

int		ft_parse_int(char *s, int *err)
{
	int		sign;
	char	*str;
	int		res;

	str = ft_strtrim(s);
	while (ft_is_wspace(*str))
		str += 1;
	if (*str == 0)
		return ft_printf(RED"ERROR"RESET" str is empty!"), 0;
	sign = get_sign(&str);
	res = 0;
	while (ft_isdigit(*str))
	{
		res = *str - 48 + res * 10;
		str++;
	}
	if (*str == 0)
		*err = 0;
	else
		*err = 1;
	return (res * sign);
}
