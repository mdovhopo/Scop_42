#include "scop.h"

bool	link_shader_prog(uint32_t *prog_id, uint32_t *shaders, uint32_t length)
{
	int		success;
	int		index;
	char	infoLog[512];

	index = length;
	*prog_id = glCreateProgram();
	while (--index > -1)
		glAttachShader(*prog_id, shaders[index]);
	glLinkProgram(*prog_id);
	glGetProgramiv(*prog_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(*prog_id, 512, NULL, infoLog);
		ft_printf("PROGRAM LINK ERR: |%s|\n", infoLog);
		return (false);
	}
	return (true);
}
