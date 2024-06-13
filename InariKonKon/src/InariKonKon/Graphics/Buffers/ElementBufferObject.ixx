module;

#include "InariKonKon/Graphics/OpenGL.hpp"

export module ElementBufferObject;

import <span>;

import OpenGLObject;
import DrawEnums;
import Typedefs;

export namespace ikk
{
	class ElementBufferObject final : public OpenGLObject
	{
	public:
		ElementBufferObject(const Usage usage = Usage::Static) noexcept;
		~ElementBufferObject() noexcept;

		void bind() const noexcept override;
		void unbind() const noexcept override;
		void release() const noexcept override;

		const GLType& getType() const noexcept;
	private:
		Usage m_usage;
		GLType m_type = GLType::None;

		template<Number T, std::size_t N>
		void BufferData(const std::span<T, N> indices) noexcept;

		friend class VertexArrayObject;
	};

	template<Number T, std::size_t N>
	inline void ElementBufferObject::BufferData(const std::span<T, N> indices) noexcept
	{
		if constexpr (std::is_same<T, std::uint8_t>::value)
			this->m_type = GLType::Unsigned_Byte;
		else if constexpr (std::is_same<T, std::uint16_t>::value)
			this->m_type = GLType::Unsigned_Short;
		else if constexpr (std::is_same<T, std::uint32_t>::value)
			this->m_type = GLType::Unsigned_Int;

		if (this->m_id == 0)
			gl->GenBuffers(1, &this->m_id);
		this->bind();
		gl->BufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T) * indices.size(), &indices[0], this->m_usage);
		this->unbind();
	}

	ElementBufferObject::ElementBufferObject(const Usage usage) noexcept : m_usage(usage)
	{
	}

	ElementBufferObject::~ElementBufferObject() noexcept
	{
		this->release();
	}

	void ElementBufferObject::bind() const noexcept
	{
		gl->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_id);
	}

	void ElementBufferObject::unbind() const noexcept
	{
		gl->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void ElementBufferObject::release() const noexcept
	{
		if (this->m_id)
			gl->DeleteBuffers(1, &this->m_id);
		this->m_id = 0;
	}

	const ikk::GLType& ElementBufferObject::getType() const noexcept
	{
		return this->m_type;
	}
}