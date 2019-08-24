/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdovhopo <mdovhopo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 12:07:04 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/24 15:06:01 by mdovhopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

const char *first_tokens[] = {
	"v",
	"vn",
	"f",
	"mtllib",
	"usemtl",
	"o",
	"s",
	NULL
};

void (*line_parsers[])(char** tokens, t_obj *obj, uint32_t line_count) = {
	&parse_vertex,
	&parse_vertex_normal,
	&parse_index,
	&parse_mtllib,
	&parse_usemtl,
	&parse_object,
	&parse_smooth
};

void	parse_obj_file(const char *path, t_obj *obj)
{
	char *line = NULL;
	uint32_t line_count = 1;
	while(ft_read_next_line(path, &line) > 0)
	{
		char *trimmed_line = ft_strtrim(line);
		// printf("[%d] -%s\n", line_count, trimmed_line);
		free(line);
		if (*trimmed_line == '#' || *trimmed_line == 0 || *trimmed_line == '\n') {
			free(trimmed_line);
			line_count++;
			continue;
		}
		char **tokens = ft_strsplit(trimmed_line, ' ');
		t_first_token token_id = find_str_in_array((char**)first_tokens, tokens[0]);
		if (token_id == -1) {}
			// throw_parsing_warning(line_count, tokens[0]);
		else
			line_parsers[token_id](tokens + 1, obj, line_count);
		line_count++;
		free_2d_arr(tokens);
		free(trimmed_line);
	}
}
