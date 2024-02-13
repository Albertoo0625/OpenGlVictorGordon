#include"shader.h"

shaderType my;



Shader::Shader(const std::string vertexFilepath, const std::string fragmentFilepath)
	:m_Renderer_Id(0)
{
	ParseReturn P=parseShader(vertexFilepath,fragmentFilepath);
	std::cout <<"fragment id " << P.fId << std::endl;
	std::cout << "vertex id " << P.vId << std::endl;
	m_Renderer_Id = linkShader(P.vId, P.fId);
}

Shader::~Shader()
{
	glDeleteProgram(m_Renderer_Id);
}

shaderType Shader::get_file_contents(const std::string filepath, const std::string term)
{
	std::ifstream contents(filepath);
	std::string shadercode;

	if (!contents.is_open()) {
		std::cerr << "Error opening file: " << filepath << std::endl;
		return my; // Or any other error code indicating failure
	}

	while (getline(contents, shadercode))
	{
		if (shadercode.find("#shader") != std::string::npos)
		{
			if (shadercode.find(term.c_str()) != std::string::npos)
			{
				std::stringstream buffer;
				buffer << contents.rdbuf();
				shadercode = buffer.str();
				my.shadercode = shadercode;
				if (term == "vertex")
				{
					my.type = GL_VERTEX_SHADER;
					contents.close();
				}
				if (term == "fragment")
				{
					my.type = GL_FRAGMENT_SHADER;
					contents.close();
				}
				return { my.shadercode,my.type };
			}
		}
	}


	return my;
}

ParseReturn Shader::parseShader(const std::string vertexFilepath, const std::string fragmentFilepath)
{
	shaderType vertexShader = get_file_contents(fragmentFilepath, "vertex");
	shaderType fragmentShader = get_file_contents(fragmentFilepath, "fragment");
	const char* vertex = vertexShader.shadercode.c_str();
	const char* fragment = fragmentShader.shadercode.c_str();
	unsigned int vId = compileShader(vertexShader.type, vertex);
	unsigned int fId = compileShader(fragmentShader.type, fragment);
	ParseReturn R;
	R.vId = vId;
	R.fId = fId;
	return R;
}

unsigned int Shader::compileShader(const unsigned int type, const char* shadersource) 
{
	unsigned int Renderer_Id = glCreateShader(type);
	glShaderSource(Renderer_Id, 1, &shadersource, NULL);
	glCompileShader(Renderer_Id);
	compileErrors(Renderer_Id, "SHADER");
	return Renderer_Id;
}

void Shader::compileErrors(unsigned int Renderer_id, const char* type)
{
	int hasCompiled;
	char infoLog[1024];

	if (type = "SHADER") {
		glGetShaderiv(Renderer_id, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(Renderer_id, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << "\n" << infoLog[0] << std::endl;
		}
	}

	if (type = "PROGRAM") {
		glGetProgramiv(Renderer_id, GL_LINK_STATUS, &hasCompiled);
		glGetProgramInfoLog(Renderer_id, 1024, NULL, infoLog);
		std::cout << "PROGRAM_COMPILATION_ERROR for:" << "\n" << infoLog << std::endl;
	}
}

unsigned int Shader::linkShader(unsigned int vertexshader, unsigned int fragmentshader)
{
	unsigned int ID = glCreateProgram();
	glAttachShader(ID, vertexshader);
	glAttachShader(ID, fragmentshader);
	glLinkProgram(ID);
	glValidateProgram(ID);
	compileErrors(ID, "PROGRAM");
	return ID;
}

void Shader::Bind() const 
{
	glUseProgram(m_Renderer_Id);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}
