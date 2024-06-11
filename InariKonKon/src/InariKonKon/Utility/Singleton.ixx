export module InariKonKon:Singleton;

import :NonCopyable;

export namespace ikk
{
    template<class T>
    class Singleton : public NonCopyable
    {
    public:
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