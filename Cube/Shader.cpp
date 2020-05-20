#include "Shader.h"
#include <string>

void Shader::load_shaders()
{
	shaderId = glCreateProgram();

	if (!shaderId) {
		printf("Error creating the shader program.\n");
		return;
	}

	std::string vertexString = load_shader_file("vertex.glsl");
	std::string fragmentString = load_shader_file("fragment.glsl");
	const char* vertex_code = vertexString.c_str();
	const char* fragment_code = fragmentString.c_str();

	compile_shader(GL_VERTEX_SHADER, vertex_code);
	compile_shader(GL_FRAGMENT_SHADER, fragment_code);

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

void Shader::compile_shader(GLenum shader_type, const char* shader_code)
{
	printf("%s", shader_code);

	GLuint shader = glCreateShader(shader_type);
	const GLchar* code[1];
	code[0] = shader_code;

	GLint code_length[1];
	code_length[0] = strlen(shader_code);

	glShaderSource(shader, 1, code, code_length);
	glCompileShader(shader);

	// Check for shader compilation error.
	GLint result = 0;
	GLchar error_log[1024] = { 0 };

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	if (!result) {
		glGetShaderInfoLog(shader, sizeof(error_log), NULL, error_log);
		printf("Error compiling the shader: %s \n", error_log);
		return;
	}

	glAttachShader(shaderId, shader);
}

std::string Shader::load_shader_file(std::string file_name)
{
	std::ifstream file(file_name, std::ios::in);
	std::string content((std::istreambuf_iterator<char>(file)),
		(std::istreambuf_iterator<char>()));
	return content;
}