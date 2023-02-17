#pragma once

#include <iostream>

#include "Renderer.h"

class Texture
{
public:
	Texture(std::string_view path);
	~Texture();

	void Bind(unsigned int slot = 0)const;
	void Unbind()const;

	inline int GetWidth()const { return m_Width; }
	inline int GetHeight()const { return m_Height; }
private:
	unsigned int m_RendererID;
	std::string_view m_Filepath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, nrChannels;// byte per pixel
};
