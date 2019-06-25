#include "scop.h"

int32_t		gl_error_report(const char *msg, const int32_t exit_code)
{
	ft_printf("Error: [%s] exit with code %d", msg, exit_code);
	glfwTerminate();
	return (exit_code);
}
