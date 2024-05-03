#pragma once

#include "InariKonKon/Graphics/Shader/Shader.hpp"

namespace ikk
{
	namespace priv
	{
		class PostFX
		{
		public:
			PostFX(const char* vertex, const char* fragment) noexcept : m_shader(vertex, fragment) {};

			PostFX(const PostFX&) noexcept = default;
			PostFX(PostFX&&) noexcept = default;

			virtual PostFX& operator=(const PostFX&) noexcept = default;
			virtual PostFX& operator=(PostFX&&) noexcept = default;

			virtual ~PostFX() noexcept = default;

			virtual void apply() noexcept = 0;
		protected:
			Shader m_shader;
		};
	}
}