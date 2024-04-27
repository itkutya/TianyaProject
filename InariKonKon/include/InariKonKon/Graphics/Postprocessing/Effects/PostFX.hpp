#pragma once

#include "InariKonKon/Graphics/Shader/Shader.hpp"

namespace ikk
{
	namespace priv
	{
		class PostFX
		{
		public:
			PostFX(const char* vertex, const char* fragment) noexcept;

			PostFX(const PostFX&) noexcept = default;
			PostFX(PostFX&&) noexcept = default;

			virtual PostFX& operator=(const PostFX&) noexcept = default;
			virtual PostFX& operator=(PostFX&&) noexcept = default;

			virtual ~PostFX() noexcept = default;

			virtual const Shader& getShader() const noexcept final;
			virtual Shader& getShader() noexcept final;
		protected:
			Shader m_shader;
		};
	}
}