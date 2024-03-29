#include"IndexBuffer.h"
#include <glad/glad.h>
#include <assert.h>


IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	:m_Renderer_Id(0), m_Count(count)
{
	assert(sizeof(unsigned int) == sizeof(GLuint));
	glGenBuffers(1,&m_Renderer_Id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer_Id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_Renderer_Id);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer_Id);
}

void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
