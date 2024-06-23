module;

#include "InariKonKon/Graphics/OpenGL.hpp"

export module VertexArrayObject;

import <span>;

import Vertex;

import ElementBufferObject;
import VertexBufferObject;
import OpenGLObject;
import Typedefs;
import Context;

export namespace ikk
{
	class VertexArrayObject final : public OpenGLObject
	{
	public:
		VertexArrayObject() noexcept;
		~VertexArrayObject() noexcept;

		void bind() const noexcept override;
		void unbind() const noexcept override;
		void release() const noexcept override;

		template<VertexType VT, std::size_t VN, Number IT, std::size_t IN>
		void setup(VertexBufferObject& vbo, const std::span<VT, VN> vertices, ElementBufferObject& ebo, const std::span<IT, IN> indices) const noexcept;
		template<VertexType VT, std::size_t VN>
		void setup(VertexBufferObject& vbo, const std::span<VT, VN> vertices) const noexcept;
	private:
		void setupVertexAttributes() const noexcept;
	};

	template<VertexType VT, std::size_t VN, Number IT, std::size_t IN>
	void VertexArrayObject::setup(VertexBufferObject& vbo, const std::span<VT, VN> vertices, ElementBufferObject& ebo, const std::span<IT, IN> indices) const noexcept
	{
		this->bind();
		vbo.BufferData(vertices);
		ebo.BufferData(indices);
		this->setupVertexAttributes();
		//this->unbind();
	}

	template<VertexType VT, std::size_t VN>
	void VertexArrayObject::setup(VertexBufferObject& vbo, const std::span<VT, VN> vertices) const noexcept
	{
		this->bind();
		vbo.BufferData(vertices);
		this->setupVertexAttributes();
		//this->unbind();
	}

	VertexArrayObject::VertexArrayObject() noexcept
	{
		gl->GenVertexArrays(1, &this->m_id);
	}

	VertexArrayObject::~VertexArrayObject() noexcept
	{
		this->release();
	}

	void VertexArrayObject::bind() const noexcept
	{
		gl->BindVertexArray(this->m_id);
	}

	void VertexArrayObject::unbind() const noexcept
	{
		gl->BindVertexArray(0);
	}

	void VertexArrayObject::release() const noexcept
	{
		if (this->m_id)
			gl->DeleteVertexArrays(1, &this->m_id);
		this->m_id = 0;
	}

	//TODO:
	//Impl this as user definable for other vertex classes...
	void VertexArrayObject::setupVertexAttributes() const noexcept
	{
		gl->EnableVertexAttribArray(0);
		gl->VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		gl->EnableVertexAttribArray(1);
		gl->VertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		gl->EnableVertexAttribArray(2);
		gl->VertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	}
}