#pragma once

#include "VertexBuffer.h"
//#include "VertexBufferLayout.h"
//#include <glad/glad.h>

class VertexBufferLayout;//避免循环引用，正规做法是把宏定义的部分写成到单独的头文件里，按需引入这个头文件

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

