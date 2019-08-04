/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 02:06:41 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/03 13:52:18 by tryckylake       ###   ########.fr       */
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

int		ft_parse_int(char *s, int *err)
{
	int		sign;
	char	*str;
	int		i;
	int		res;

	str = ft_strtrim(s);
	i = -1;
	while (ft_is_wspace(str[++i]))
		;
	if (str[i] == 0)
		return ft_printf(RED"ERROR"RESET" str is empty!"), 0;
	sign = get_sign(&str[i], &i);
	res = 0;
	while (ft_isdigit(str[i]))
	{
		res = str[i] - 48 + res * 10;
		i++;
	}
	if (str[i] == 0)
		*err = 0;
	else
		*err = 1;
	free(str);
	return (res * sign);
}
