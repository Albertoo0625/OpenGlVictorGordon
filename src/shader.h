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

struct ParseReturn {
	unsigned int vId;
	unsigned int fId;
};

class Shader {
private:
	unsigned int m_Renderer_Id;

public:
	Shader(const std::string vertexFilepath, const std::string fragmentFilepath);
	~Shader();
	void Bind() const;
	void Unbind() const;

public:
	shaderType get_file_contents(const std::string filepath, const std::string term);
	ParseReturn parseShader(const std::string vertexFilepath, const std::string fragmentFilepath);
	unsigned int compileShader(const unsigned int type, const char* shadersource);
	void compileErrors(unsigned int Renderer_id, const char* type);	
	unsigned int linkShader(unsigned int vertexshader, unsigned int fragmentshader);
	
};
