#pragma once

#include "InariKonKon/Entity/Components/EntityComponentBase.hpp"
#include "InariKonKon/Graphics/Buffers/ElementBufferObject.hpp"
#include "InariKonKon/Graphics/Buffers/VertexBufferObject.hpp"
#include "InariKonKon/Graphics/Buffers/VertexArrayObject.hpp"
#include "InariKonKon/Graphics/Texture/Texture.hpp"
#include "InariKonKon/Graphics/Draw/DrawEnums.hpp"
#include "InariKonKon/Graphics/Shader/Shader.hpp"
#include "InariKonKon/Graphics/OpenGL/OpenGL.hpp"
#include "InariKonKon/Utility/Math/Rect.hpp"

namespace ikk
{
	class Window;

	class DrawableComponent : public EntityComponent<1>
	{
	public:
	private:
		priv::VertexArrayObject m_VAO;
		priv::VertexBufferObject m_VBO;
		priv::ElementBufferObject m_EBO;

		void draw() const noexcept {};

		friend class Window;
	};
}