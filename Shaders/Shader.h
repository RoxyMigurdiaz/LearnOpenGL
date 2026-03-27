#pragma once

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader
{
public:
	// 读取并构建着色器
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	// 使用/激活程序
	void use();
	// uniform工具函数
	void setBool(const std::string& name, bool value);
	void setFloat(const std::string& name, float value);
	void setInt(const std::string& name, int value);

	unsigned int programID;
};