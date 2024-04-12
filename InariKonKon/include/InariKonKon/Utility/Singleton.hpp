#pragma once

#include "InariKonKon/Utility/NonCopyable.hpp"

namespace ikk
{
	template<class T>
	class Singleton : public NonCopyable
	{
    public:
        constexpr Singleton(const Singleton&) noexcept = delete;
        constexpr Singleton(Singleton&) noexcept = delete;
        constexpr Singleton(Singleton&&) noexcept = delete;

        virtual constexpr Singleton& operator=(const Singleton&) noexcept = delete;
        virtual constexpr Singleton& operator=(Singleton&) noexcept = delete;
        virtual constexpr Singleton& operator=(Singleton&&) noexcept = delete;
        
        virtual constexpr ~Singleton() noexcept = default;

        [[nodiscard]] static T& getInstance() noexcept;
    protected:
        constexpr Singleton() noexcept = default;
	};

    template<class T>
    inline T& Singleton<T>::getInstance() noexcept
    {
        static T instance;
        return instance;
    }
}