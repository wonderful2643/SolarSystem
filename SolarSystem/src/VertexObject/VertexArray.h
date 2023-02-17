#pragma once

class VertexBufferLayout;//避免循环引用，正规做法是把宏定义的部分写成到单独的头文件里，按需引入这个头文件

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBufferLayout& layout);

	void Bind()const;
	void Unbind()const;
private:
	unsigned int m_RendererID;
};

