#pragma once

#include <string>

namespace ikk
{
	namespace priv
	{
		class PostFX
		{
		public:
			PostFX(const std::string& effect) noexcept : m_effect(effect) {};

			PostFX(const PostFX&) noexcept = default;
			PostFX(PostFX&&) noexcept = default;

			virtual PostFX& operator=(const PostFX&) noexcept = default;
			virtual PostFX& operator=(PostFX&&) noexcept = default;

			virtual ~PostFX() noexcept = default;
		protected:
			std::string m_effect;
		};
	}
}