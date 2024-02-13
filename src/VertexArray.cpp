// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include "VertexArray.h"
#include <iostream>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_Renderer_id);

}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_Renderer_id);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_Renderer_id);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (int i = 0; i < elements.size();i++) {
		const auto& element = elements[i];
		std::cout << "normalized " << element.normalized << std::endl;
		std::cout << "type " << element.type << std::endl;
		std::cout << "count " << element.count << std::endl;
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * sizeof(element.type);
	
		glEnableVertexAttribArray(i);
	}
}










