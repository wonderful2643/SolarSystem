#pragma once

#include "VertexBuffer.h"
//#include "VertexBufferLayout.h"
//#include <glad/glad.h>

class VertexBufferLayout;//����ѭ�����ã����������ǰѺ궨��Ĳ���д�ɵ�������ͷ�ļ�������������ͷ�ļ�

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind()const;
	void Unbind()const;
	void Delete()const;
private:
	unsigned int m_RendererID;
};

