#include "scop.h"

void processInput(GLFWwindow *window, float *angle_x, float *angle_y, float *far)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		*angle_y = clamp(0, 360, *angle_y -= 1);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		*angle_y = clamp(0, 360, *angle_y += 1);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		*angle_x = clamp(0, 360, *angle_x += 1);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		*angle_x = clamp(0, 360, *angle_x -= 1);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		*far = clamp(-10, 10, *far += 0.01f);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		*far = clamp(-10, 10, *far -= 0.01f);
}

const float vertices[] = {
// 	 x		y	  z		 r	   g	 b
    //  0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // top right
    //  0.5f, -0.5f, 0.0f,  0.0f, 0.6f, 0.0f, // bottom right
    // -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // bottom left
    // -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f, // top left 
    -0.5f,-0.5f,-0.5f,     0.583f,  0.771f,  0.014f, // triangle 1 : begin
    -0.5f,-0.5f, 0.5f,     0.609f,  0.115f,  0.436f,
    -0.5f, 0.5f, 0.5f,     0.327f,  0.483f,  0.844f, // triangle 1 : end
    0.5f, 0.5f,-0.5f,      0.822f,  0.569f,  0.201f, // triangle 2 : begin
    -0.5f,-0.5f,-0.5f,     0.435f,  0.602f,  0.223f,
    -0.5f, 0.5f,-0.5f,     0.310f,  0.747f,  0.185f,// triangle 2 : end
    0.5f,-0.5f, 0.5f,      0.597f,  0.770f,  0.761f,
    -0.5f,-0.5f,-0.5f,     0.559f,  0.436f,  0.730f,
    0.5f,-0.5f,-0.5f,      0.359f,  0.583f,  0.152f,
    0.5f, 0.5f,-0.5f,      0.483f,  0.596f,  0.789f,
    0.5f,-0.5f,-0.5f,      0.559f,  0.861f,  0.639f,
    -0.5f,-0.5f,-0.5f,     0.195f,  0.548f,  0.859f,
    -0.5f,-0.5f,-0.5f,     0.014f,  0.184f,  0.576f,
    -0.5f, 0.5f, 0.5f,     0.771f,  0.328f,  0.970f,
    -0.5f, 0.5f,-0.5f,     0.406f,  0.615f,  0.116f,
    0.5f,-0.5f, 0.5f,      0.676f,  0.977f,  0.133f,
    -0.5f,-0.5f, 0.5f,     0.971f,  0.572f,  0.833f,
    -0.5f,-0.5f,-0.5f,     0.140f,  0.616f,  0.489f,
    -0.5f, 0.5f, 0.5f,     0.997f,  0.513f,  0.064f,
    -0.5f,-0.5f, 0.5f,     0.945f,  0.719f,  0.592f,
    0.5f,-0.5f, 0.5f,      0.543f,  0.021f,  0.978f,
    0.5f, 0.5f, 0.5f,      0.279f,  0.317f,  0.505f,
    0.5f,-0.5f,-0.5f,      0.167f,  0.620f,  0.077f,
    0.5f, 0.5f,-0.5f,      0.347f,  0.857f,  0.137f,
    0.5f,-0.5f,-0.5f,      0.055f,  0.953f,  0.042f,
    0.5f, 0.5f, 0.5f,      0.714f,  0.505f,  0.345f,
    0.5f,-0.5f, 0.5f,      0.783f,  0.290f,  0.734f,
    0.5f, 0.5f, 0.5f,      0.722f,  0.645f,  0.174f,
    0.5f, 0.5f,-0.5f,      0.302f,  0.455f,  0.848f,
    -0.5f, 0.5f,-0.5f,     0.225f,  0.587f,  0.040f,
    0.5f, 0.5f, 0.5f,      0.517f,  0.713f,  0.338f,
    -0.5f, 0.5f,-0.5f,     0.053f,  0.959f,  0.120f,
    -0.5f, 0.5f, 0.5f,     0.393f,  0.621f,  0.362f,
    0.5f, 0.5f, 0.5f,      0.673f,  0.211f,  0.457f,
    -0.5f, 0.5f, 0.5f,     0.820f,  0.883f,  0.371f,
    0.5f,-0.5f, 0.5f,      0.982f,  0.099f,  0.879f
};

const uint32_t indices[] = {
	0, 1, 3,
	1, 2, 3
};
// TODO refactor vec and mat as aligned float arrays
int main(void) {
	float angle_x = 45;
	float angle_y = 45;
	float far = -5;
	t_mat4 t_model = mat_identity();
	t_model = mat_rotate(t_model, VEC(0, 1, 0, 1), DEG_TO_RAD(angle_x));
	t_model = mat_rotate(t_model, VEC(1, 0, 0, 1), DEG_TO_RAD(angle_y));
	float test_model[4][4] = {0};
	for (int i = 0; i < 4 ; i++)
		for (int j = 0; j < 4; j++)
			test_model[i][j] = t_model[j * 4 + i];
	mat4 model;
	glm_mat4_identity(model);
	glm_rotate(model, glm_rad(angle_x), (vec3){0, 1, 0});
	glm_rotate(model, glm_rad(angle_y), (vec3){1, 0, 0});
	t_mat4 t_view = mat_identity();
	t_view = mat_translate(t_view, VEC(0, 0, far, 1));
	mat4 view;//
	glm_mat4_identity(view);
	glm_translate(view, (vec3){0, 0, far});
	mat4 proj;
	glm_mat4_identity(proj);
	glm_perspective(glm_rad(45.0f), 1, 0.1f, 100.0f, proj);
	glm_mat4_print(view, stdout);
	ft_printf("My\n%+m", t_view);
}

int main_test(void)
{
	GLFWwindow	*window;
	char		*vertShaderCode;
	char		*fragShaderCode;
	uint32_t	vertShaderId;
	uint32_t	fragShaderId;
	uint32_t	shaderProg;

	ft_printf("####       Start        ####\n");
	if (!gl_init("Scop", 800, 800, &window))
		return (gl_error_report("OpenGL could not init :(", -1));
	print_gl_info();
	// Read shaders from source

	// TODO make gl_env struct and move all this stuff to gl_init
	fragShaderCode = ft_read_file(FRAGMENT_SHADER_PATH);
	vertShaderCode = ft_read_file(VERTEX_SHADER_PATH);

	// Compile shaders
	if(!compile_shader(&vertShaderId, vertShaderCode, GL_VERTEX_SHADER, VERTEX_SHADER_PATH))
		return (-1);
	if (!compile_shader(&fragShaderId, fragShaderCode, GL_FRAGMENT_SHADER, FRAGMENT_SHADER_PATH))
		return (-1);
	free(vertShaderCode);
	free(fragShaderCode);
	// Link Program
	if (!link_shader_prog(&shaderProg, (uint32_t[]){vertShaderId, fragShaderId}, 2))
		return (-1);
	glDeleteShader(vertShaderId);
	glDeleteShader(fragShaderId);  

	uint32_t vao; // vertex_attrib_arr
	uint32_t ebo; // element_buffer_obj
	uint32_t vbo; // vertex_buffer_object
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	// glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 216 * sizeof(float), vertices, GL_STATIC_DRAW);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glUseProgram(shaderProg);
	uint32_t model_loc = glGetUniformLocation(shaderProg, "model");
	uint32_t proj_loc = glGetUniformLocation(shaderProg, "projection");
	uint32_t view_loc = glGetUniformLocation(shaderProg, "view");
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	if (glGetError() != GL_NO_ERROR)
		ft_printf("WARNING glError: %d", glGetError());
	float angle_x = 45;
	float angle_y = 45;
	float far = -5;
	// mat4 proj, view, model;
	// glm_mat4_identity(proj);
	// glm_mat4_identity(view);
	// glm_mat4_identity(model);
	// // glm_translate(model, (vec3){1, 2, 3});
	// glm_rotate(model, glm_rad(45.0f) , (vec3){1, 2, 3});
	// t_mat4 t_proj = mat_identity();
	// t_mat4 t_view = mat_identity();
	// t_mat4 t_model = mat_identity();
	// // t_model = mat_translate(t_model, VEC(1, 2, 3, 1));
	// t_model = mat_rotate(t_model, VEC(1, 2, 3, 1), DEG_TO_RAD(45.0f));
	// ft_printf("My\n%m", t_model);
	// glm_mat4_print(model, stdout);
	int i = 0;
	t_mat4 t_model = mat_identity();
	t_model = mat_rotate(t_model, VEC(0, 1, 0, 1), DEG_TO_RAD(angle_x));
	t_model = mat_rotate(t_model, VEC(1, 0, 0, 1), DEG_TO_RAD(angle_y));
	mat4 model;
	glm_mat4_identity(model);
	glm_rotate(model, glm_rad(angle_x), (vec3){0, 1, 0});
	glm_rotate(model, glm_rad(angle_y), (vec3){1, 0, 0});
	t_mat4 t_view = mat_identity();
	t_view = mat_translate(t_view, VEC(0, 0, far, 1));
	mat4 view;//
	glm_mat4_identity(view);
	glm_translate(view, (vec3){0, 0, far});
	mat4 proj;
	glm_mat4_identity(proj);
	glm_perspective(glm_rad(45.0f), 1, 0.1f, 100.0f, proj);
	glm_mat4_print(view, stdout);
	ft_printf("My\n%+m", t_view);
	while (!glfwWindowShouldClose(window))
	{
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, (float*)&t_model);
		glUniformMatrix4fv(view_loc, 1, GL_FALSE, (float*)&t_view);
		glUniformMatrix4fv(proj_loc, 1, GL_FALSE, proj[0]);
		processInput(window, &angle_x, &angle_y, &far);
		glClearColor(68 / (float)255, 85 / (float)255, 90 / (float)255, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	ft_printf("#### IT IS FINALLY ENDED! ####\n");
	return (0);
}
