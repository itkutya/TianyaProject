#include "InariKonKon/Graphics/Buffers/VertexArrayObject.hpp"

#include "InariKonKon/Graphics/Vertex/Vertex.hpp"
#include "InariKonKon/Graphics/OpenGL/OpenGL.hpp"

namespace ikk
{
	namespace priv
	{
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
}