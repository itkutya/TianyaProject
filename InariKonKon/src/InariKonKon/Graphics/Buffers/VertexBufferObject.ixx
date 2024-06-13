module;

#include "InariKonKon/Graphics/OpenGL.hpp"

export module VertexBufferObject;

import <span>;

import OpenGLObject;
import DrawEnums;
import Typedefs;

export namespace ikk
{
	class VertexBufferObject final : public OpenGLObject
	{
	public:
		VertexBufferObject(const Usage usage = Usage::Static) noexcept;
		~VertexBufferObject() noexcept;

		void bind() const noexcept override;
		void unbind() const noexcept override;
		void release() const noexcept override;
	private:
		Usage m_usage;

		template<VertexType T, std::size_t N>
		void BufferData(const std::span<T, N> vertices) const noexcept;

		friend class VertexArrayObject;
	};

	template<VertexType T, std::size_t N>
	inline void VertexBufferObject::BufferData(const std::span<T, N> vertices) const noexcept
	{
		if (this->m_id == 0)
			gl->GenBuffers(1, &this->m_id);
		this->bind();
		gl->BufferData(GL_ARRAY_BUFFER, sizeof(T) * vertices.size(), &vertices[0], this->m_usage);
	}

	VertexBufferObject::VertexBufferObject(const Usage usage) noexcept : m_usage(usage)
	{
	}

	VertexBufferObject::~VertexBufferObject() noexcept
	{
		this->release();
	}

	void VertexBufferObject::bind() const noexcept
	{
		gl->BindBuffer(GL_ARRAY_BUFFER, this->m_id);
	}

	void VertexBufferObject::unbind() const noexcept
	{
		gl->BindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBufferObject::release() const noexcept
	{
		if (this->m_id)
			gl->DeleteBuffers(1, &this->m_id);
		this->m_id = 0;
	}
}