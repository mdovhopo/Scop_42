#ifndef SCOP_H
# define SCOP_H

# include "libft.h"

# include <stdio.h>
# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <cglm/cglm.h>

// TODO move this to env struct

# define WIDTH 800
# define HEIGHT 600

#define VERTEX_SHADER_PATH		"./src/shaders/vertShader.vert"
#define FRAGMENT_SHADER_PATH	"./src/shaders/fragShader.frag"

/*
** Init enviroment
*/

bool	gl_init(const char *window_name,
				const uint32_t w,
				const uint32_t h,
				GLFWwindow **win);
bool	compile_shader(	uint32_t *shader_id,
						const char* source,
						int32_t type,
						const char* name);
bool	link_shader_prog(uint32_t *prog_id, uint32_t *shaders, uint32_t length);

/*
** Utils
*/

void	print_gl_info(void);
ssize_t	get_file_size(const char *path);
char	*read_file(const char *path);

/*
** Error handle
*/

int32_t		gl_error_report(const char *msg, const int32_t exit_code);

#endif
