#include "scop.h"

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float yaw = -90.0f;
float pitch = 0;

float lastX;
float lastY;
bool firstMouse = true;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; 
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw   += xoffset;
	pitch += yoffset;
	if(pitch > 89.0f)
		pitch =  89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;
}

void processInput(GLFWwindow *window, t_vec4 *cameraPos, t_vec4 *cameraFront, t_vec4 *cameraUp)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    float cameraSpeed = 5.0f * deltaTime; // adjust accordingly
	// TODO MacOS Clang cant multiply float and vector. Do smth with this 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        *cameraPos += VEC(cameraSpeed, cameraSpeed, cameraSpeed, cameraSpeed) * *cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        *cameraPos -=  VEC(cameraSpeed, cameraSpeed, cameraSpeed, cameraSpeed) * *cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        *cameraPos -= vec_unit(vec_cross(*cameraFront, *cameraUp)) *  VEC(cameraSpeed, cameraSpeed, cameraSpeed, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        *cameraPos += vec_unit(vec_cross(*cameraFront, *cameraUp)) *  VEC(cameraSpeed, cameraSpeed, cameraSpeed, cameraSpeed);
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

t_vec4 cube_pos[10] = {
  VEC( 0.0f,  0.0f,  0.0f, 0), 
  VEC( 2.0f,  5.0f, -15.0f, 0), 
  VEC(-1.5f, -2.2f, -2.5f, 0),  
  VEC(-3.8f, -2.0f, -12.3f, 0),  
  VEC( 2.4f, -0.4f, -3.5f, 0),  
  VEC(-1.7f,  3.0f, -7.5f, 0),  
  VEC( 1.3f, -2.0f, -2.5f, 0),  
  VEC( 1.5f,  2.0f, -2.5f, 0), 
  VEC( 1.5f,  0.2f, -1.5f, 0), 
  VEC(-1.3f,  1.0f, -1.5f, 0)
};

const uint32_t indices[] = {
	0, 1, 3,
	1, 2, 3
};

int main(void)
{
	GLFWwindow	*window;
	char		*vertShaderCode;
	char		*fragShaderCode;
	uint32_t	vertShaderId;
	uint32_t	fragShaderId;
	uint32_t	shaderProg;

	ft_printf("####       Start        ####\n");
	if (!gl_init("Scop", WIDTH, HEIGHT, &window))
		return (gl_error_report("OpenGL could not init :(", -1));
	glfwSetCursorPosCallback(window, mouse_callback);
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
	t_mat4 proj = mat_identity();
	proj = mat_perspective(DEG_TO_RAD(45), WIDTH/(float)HEIGHT, 0.1f, 100.0f);
	// t_mat4 view = mat_identity();
	// view = mat_translate(view, VEC(0, 0, cam_z, 1));
	glUniformMatrix4fv(proj_loc, 1, GL_TRUE, (float*)&proj);
	glClearColor(68 / (float)255, 85 / (float)255, 90 / (float)255, 1.0f);
	t_vec4 cam_pos = VEC3(0, 0, 3);
	t_vec4 cam_front = VEC3(0, 0, -1);
	t_vec4 cam_up = VEC3(0, 1, 0);
	t_vec4 dir = {};
	// float pitch = 0;
	// float yaw = 0;
	ft_printf("%v", dir);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		dir[0] = cos(DEG_TO_RAD(pitch)) * cos(DEG_TO_RAD(yaw));
		dir[1] = sin(DEG_TO_RAD(pitch));
		dir[2] = cos(DEG_TO_RAD(pitch)) * sin(DEG_TO_RAD(yaw));
		cam_front = vec_unit(dir);
		t_mat4 view = mat_look_at(cam_pos, cam_pos + cam_front, cam_up);
		// t_mat4 view = mat_look_at(VEC3(cam_x, 0, cam_z), VEC3(0, 0, 0), VEC3(0, 1, 0));
		glUniformMatrix4fv(view_loc, 1, GL_TRUE, (float*)&view);
		for (int i = 0; i < 10; i++) {
			t_mat4 model = mat_identity();
			model = mat_translate(model, cube_pos[i]);
			model = mat_rotate(model, VEC(1, 0.3f, 0.5f, 0), (float)glfwGetTime() * DEG_TO_RAD(30.0f * (i + 1)));
			glUniformMatrix4fv(model_loc, 1, GL_TRUE, (float*)&model);
			glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
		}
		processInput(window, &cam_pos, &cam_front, &cam_up);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	ft_printf("#### IT IS FINALLY ENDED! ####\n");
	return (0);
}
