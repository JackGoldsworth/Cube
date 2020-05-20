#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

#pragma once
class Shader
{
public:
	void load_shaders();
	GLuint shaderId;
private:
	void compile_shader(GLenum shader_type);
	void load_shader_file(std::string file_name, char* data);
};

