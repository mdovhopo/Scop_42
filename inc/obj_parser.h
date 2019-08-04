/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 14:01:54 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/03 14:23:30 by tryckylake       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_PARSER_H
# define OBJ_PARSER_H

# include "libft.h"

typedef enum	e_first_token
{
	VERTEX = 0,
	INDEX,
	MTLLIB,
	USEMTL,
	OBJECT,
	SMOOTH
}				t_first_token;

typedef	struct	s_mtl
{
	char *name;
}				t_mtl;

typedef struct	s_obj
{
	t_vec4		*vertices;
	uint32_t	vert_len;
	t_veci3		*indices;
	uint32_t	indices_len;
	t_mtl		material;
	float		smooth;
}				t_obj;

void	parse_obj_file(const char *path, t_obj *obj);

float	ft_parse_float(char *s, int *err);
int		ft_parse_int(char *s, int *err);

/*
** line parsers
*/

void	parse_index(char** tokens, t_obj *obj, uint32_t line_count);
void	parse_vertex(char** tokens, t_obj *obj, uint32_t line_count);
void	parse_object(char** tokens, t_obj *obj, uint32_t line_count);
void	parse_usemtl(char** tokens, t_obj *obj, uint32_t line_count);
void	parse_mtllib(char** tokens, t_obj *obj, uint32_t line_count);
void	parse_smooth(char** tokens, t_obj *obj, uint32_t line_count);


/*
** Error handle
*/

void	throw_parsing_error(uint32_t line_count, char *token, char *msg);

/*
** Utils
*/

int32_t	find_str_in_array(char** arr, char* to_find);
void	free_2d_arr(char **arr);

#endif
