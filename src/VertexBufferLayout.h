#pragma once
#include<vector>
#include"glad/glad.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned int normalized;
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement>m_Elements;
	unsigned int m_stride;
public:
	VertexBufferLayout() :m_stride(0) {};

	template<typename T>
	void push(unsigned int count);

	template<>
	void push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT,count,GL_FALSE });
		m_stride += count * sizeof(GL_FLOAT);
	};


	template <>
	void push<int>(unsigned int count)
	{
		m_Elements.push_back({ GL_INT, count, GL_FALSE });
		m_stride += count * sizeof(GLint);
	}

	inline std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_stride; }
};



