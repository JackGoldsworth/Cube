#include "Shader.h"
#include <string>

void Shader::load_shaders()
{
	shaderId = glCreateProgram();

	if (!shaderId) {
		printf("Error creating the shader program.\n");
		return;
	}

	compile_shader(GL_VERTEX_SHADER);
	compile_shader(GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar error_log[1024] = { 0 };

	// Link the shader.
	glLinkProgram(shaderId);

	// Check for a linking error.
	glGetProgramiv(shaderId, GL_LINK_STATUS, &result);

	if (!result) {
		glGetProgramInfoLog(shaderId, sizeof(error_log), NULL, error_log);
		printf("Error linking the program: %s \n", error_log);
		return;
	}

	// Check for a validation error.
	glValidateProgram(shaderId);
	
	glGetProgramiv(shaderId, GL_VALIDATE_STATUS, &result);

	if (!result) {
		glGetProgramInfoLog(shaderId, sizeof(error_log), NULL, error_log);
		printf("Error validating the program: %s \n", error_log);
		return;
	}


}

void Shader::compile_shader(GLenum shader_type)
{
	char* file_data = new char[1024];
	if (shader_type == GL_VERTEX_SHADER)
	{
		load_shader_file("vertex.glsl", file_data);
	}
	else
	{
		load_shader_file("fragment.glsl", file_data);
	}

	printf("%s", file_data);

	GLint result = 0;
	GLchar error_log[1024] = { 0 };

	GLuint empty_shader = glCreateShader(shader_type);
	const GLchar* code[1];
	code[0] = file_data;

	GLint code_length[1];
	code_length[0] = strlen(file_data);

	glShaderSource(empty_shader, 1, code, code_length);
	glCompileShader(empty_shader);

	// Check for shader compilation error.
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

	if (!result) {
		glGetShaderInfoLog(empty_shader, sizeof(error_log), NULL, error_log);
		printf("Error compiling the shader: %s \n", error_log);
		return;
	}

	glAttachShader(shaderId, empty_shader);

	delete(file_data);
}

void Shader::load_shader_file(std::string file_name, char* data)
{
	std::ifstream file;
	file.open(file_name);

	while (!file.eof()) {
		for (int i = 0; i <= 1024; i++) {
			data[i] = file.get();
		}
	}
}