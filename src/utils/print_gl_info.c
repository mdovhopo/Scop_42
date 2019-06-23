#include "scop.h"

void	print_gl_info(void)
{
	printf("VENDOR: %s\nRENDERER: %s\nVERSION: %s\n", 
		glGetString(GL_VENDOR),
		glGetString(GL_RENDERER),
		glGetString(GL_VERSION)
	);
}
