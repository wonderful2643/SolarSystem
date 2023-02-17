#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

Texture::Texture(std::string_view path)
	: m_RendererID(0), m_Filepath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0)
{
	std::string_view sub_str = path.substr(path.find_last_of('.') + 1);
	nrChannels = (sub_str == "png") ? 4 : 3;
	//stbi_set_flip_vertically_on_load(1);

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// glTexParameteri的i表示int
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//若采用GL_CLAMP_TO_BORDER，球体拼接处会存在黑线

	m_LocalBuffer = stbi_load(path.data(), &m_Width, &m_Height, &nrChannels, 0);// 第四个参数表示channels，png图片有4通道rgba故为4 
	if (m_LocalBuffer)
	{
		if (nrChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
		else if (nrChannels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer);
		else
			std::cout << "Texture isn't png/jpg" << std::endl;

		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(m_LocalBuffer);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot); 
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
