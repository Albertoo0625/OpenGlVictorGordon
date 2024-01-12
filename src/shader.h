#pragma once
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
#include<glad/glad.h>

struct shaderType {
	std::string shadercode;
	unsigned int type = 0;
};



class Shader {
public:
	shaderType get_file_contents(const std::string filepath, const std::string term);
	void parseShader();
	unsigned int compileShader(const unsigned int type, const char* shadersource);
	void compileErrors(unsigned int Renderer_id, const char* type);	
	void linkShader(unsigned int vertexshader, unsigned int fragmentshader);
};
