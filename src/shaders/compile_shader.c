#include "scop.h"

bool	compile_shader(uint32_t *shader_id, const char* source, int32_t type)
{
	int		success;
	char	infoLog[512];

	*shader_id = glCreateShader(type);
	glShaderSource(*shader_id, 1, (const char *const *)&source, NULL);
	glCompileShader(*shader_id);
	glGetShaderiv(*shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*shader_id, 512, NULL, infoLog);
		printf("SHADER ERROR: [%s]", infoLog);
		return (false);
	}
	return (true);
}