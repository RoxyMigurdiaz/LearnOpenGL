#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// 打开文件
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n" << e.what() << std::endl;
	}

	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	unsigned int vertexShader, fragmentShader;
	int success;
	char infoLog[512];

	// -----------VertexShader------------
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::VERTEX::SHADER::COMPILE_FAILED\n" << infoLog << std::endl;
	}

	// -----------FragmentShader------------
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::FRAGMENT::SHADER::COMPILE_FAILED\n" << infoLog << std::endl;
	}

	// -----------Program-----------------
	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(programID);
}

void Shader::use()
{
	glUseProgram(programID);
}

void Shader::setBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat4)
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat4[0][0]);
}
