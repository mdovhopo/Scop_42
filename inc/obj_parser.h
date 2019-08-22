/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tryckylake <tryckylake@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 14:01:54 by tryckylake        #+#    #+#             */
/*   Updated: 2019/08/21 17:19:29 by tryckylake       ###   ########.fr       */
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

typedef enum	e_obj_manage_type
{
	OBJ_ROTATE,
	OBJ_TRANSLATE
}				t_obj_manage_type;

typedef struct	s_vertex
{
	t_vec4	point;
	t_vec4	normal;
}				t_vertex;

typedef struct	s_obj
{
	t_vertex			*vertices;
	uint32_t			vertices_len;
	t_vec4				*points;
	uint32_t			points_len;
	t_vec4				*normals;
	uint32_t			normals_len;
	t_veci3				*indices;
	uint32_t			indices_len;
	t_mtl				material;
	t_vec4				farest_point;
	float				smooth;
	t_obj_manage_type	manage_type;
	t_vec4				rot;
	t_vec4				trans;
}				t_obj;

void	parse_obj_file(const char *path, t_obj *obj);

float	ft_parse_float(char *s, int *err);
int		ft_parse_int(char *s, int *err);

/*
** line parsers
*/

void	parse_index(char** tokens, t_obj *obj, uint32_t line_count);
void	parse_vertex_normal(char** tokens, t_obj *obj, uint32_t line_count);
void	parse_vertex(char** tokens, t_obj *obj, uint32_t line_count);
void	parse_object(char** tokens, t_obj *obj, uint32_t line_count);
void	parse_usemtl(char** tokens, t_obj *obj, uint32_t line_count);
void	parse_mtllib(char** tokens, t_obj *obj, uint32_t line_count);
void	parse_smooth(char** tokens, t_obj *obj, uint32_t line_count);


/*
** Error handle
*/

void	throw_parsing_error(uint32_t line_count, char *token, char *msg);
void	throw_parsing_warning(uint32_t line_count, char *token);

/*
** Utils
*/

int32_t	find_str_in_array(char** arr, char* to_find);
void	free_2d_arr(char **arr);

#endif
