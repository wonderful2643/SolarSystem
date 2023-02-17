#pragma once

#include<glad/glad.h>
#include <glm/glm.hpp>

#include<fstream>
#include<sstream>
#include<iostream>

class Shader
{
public:
	GLuint ID;

	// Constructor(��ɫ�����캯��)
	Shader(std::string_view vertexPath, std::string_view fragmentPath)
	{
		//�ļ���ȡϵ�еı�������
		std::string vertexCode, fragmentCode;
		std::ifstream vShaderFile, fShaderFile;
		// �쳣���ƴ�����֤ifstream��������׳��쳣��
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vShaderFile.open(vertexPath.data());
			fShaderFile.open(fragmentPath.data());
			std::stringstream vShaderStream, fShaderStream;

			// ��ȡ�ļ��Ļ������ݵ���������
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			// ת����������string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure& e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		}

		/* �� string ���͵��ַ���ת��Ϊ char���� ���� */
		const GLchar* vShaderCode = vertexCode.data();
		const GLchar* fShaderCode = fragmentCode.data();

		//������ɫ��
		GLuint vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, nullptr);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		//Ƭ����ɫ��
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, nullptr);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		//��ɫ������
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");

		// ɾ����ɫ���������ӵ����򣬲�����Ҫ
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void Bind()const
	{
		glUseProgram(ID);
	}
	void Unbind() const
	{
		glUseProgram(0);
	}
	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(std::string_view name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.data()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(std::string_view name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.data()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(std::string_view name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.data()), value);
	}
	// ------------------------------------------------------------------------
	void setVec2(std::string_view name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.data()), 1, &value[0]);
	}
	void setVec2(std::string_view name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(ID, name.data()), x, y);
	}
	// ------------------------------------------------------------------------
	void setVec3(std::string_view name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.data()), 1, &value[0]);
	}
	void setVec3(std::string_view name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.data()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void setVec4(std::string_view name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.data()), 1, &value[0]);
	}
	void setVec4(std::string_view name, float x, float y, float z, float w) const
	{
		glUniform4f(glGetUniformLocation(ID, name.data()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void setMat2(std::string_view name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.data()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat3(std::string_view name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.data()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat4(std::string_view name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.data()), 1, GL_FALSE, &mat[0][0]);
	}

private:
	void checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};
