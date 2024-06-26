export module OpenGLObject;

import <cstdint>;
import <utility>;

export namespace ikk
{
	class OpenGLObject
	{
	public:
		OpenGLObject(const std::uint32_t id = 0) noexcept;

		OpenGLObject(const OpenGLObject& other) noexcept;
		OpenGLObject(OpenGLObject&& other) noexcept;

		virtual OpenGLObject& operator=(const OpenGLObject& other) noexcept final;
		virtual OpenGLObject& operator=(OpenGLObject&& other) noexcept final;

		virtual ~OpenGLObject() noexcept = default;

		virtual void bind() const noexcept = 0;
		virtual void unbind() const noexcept = 0;
		virtual void release() const noexcept = 0;

		virtual const std::uint32_t& getNativeHandle() const noexcept final;
	protected:
		mutable std::uint32_t m_id = 0;
	};

	OpenGLObject::OpenGLObject(const std::uint32_t id) noexcept : m_id(id)
	{
	}

	OpenGLObject::OpenGLObject(const OpenGLObject& other) noexcept : m_id(std::exchange(other.m_id, 0))
	{
	}

	OpenGLObject::OpenGLObject(OpenGLObject&& other) noexcept : m_id(std::exchange(other.m_id, 0))
	{
	}

	OpenGLObject& OpenGLObject::operator=(const OpenGLObject& other) noexcept
	{
		if (this != &other)
		{
			this->release();
			this->m_id = other.m_id;
			other.m_id = 0;
		}
		return *this;
	}

	OpenGLObject& OpenGLObject::operator=(OpenGLObject&& other) noexcept
	{
		if (this != &other)
		{
			this->release();
			this->m_id = other.m_id;
			other.m_id = 0;
		}
		return *this;
	}

	const std::uint32_t& OpenGLObject::getNativeHandle() const noexcept
	{
		return this->m_id;
	}
}