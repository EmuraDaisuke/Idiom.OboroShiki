#pragma once
// Copyright(c) 2018 Emura Daisuke
// Apache License 2.0



#include <cstddef>
#include <malloc.h>

#if _MSC_VER//[
// msvc
#define alloca      _alloca
#elif __clang__//][
// clang
#else//][
// gcc
#endif//]

#define local_alloc(T, s)       static_cast<T*>(alloca(s))

#define make_local(T, ...)      local_ptr<T>(local_alloc(T, T::local_size()), ##__VA_ARGS__)
#define make_local_ext(T, ...)  local_ptr<T>(local_alloc(T, T::local_size(__VA_ARGS__)), ##__VA_ARGS__)



template <class T>
class local_ptr final {
    public:
        ~local_ptr() noexcept                                               { reset(); }
        
        constexpr local_ptr() noexcept                                      :mp(nullptr){}
        constexpr local_ptr(std::nullptr_t) noexcept                        :mp(nullptr){}
        template <class... Args> explicit local_ptr(T* p, Args... args)     :mp(p){ mp->local_init(args...); }
        
        local_ptr(local_ptr<T>&& rhs) noexcept                              { mp = rhs.release(); }
        local_ptr<T>& operator =(local_ptr<T>&& rhs) noexcept               { mp = rhs.release(); return *this; }
        
        T& operator *() const noexcept                                      { return *get(); }
        T* const operator ->() const noexcept                               { return mp; }
        explicit operator bool() const noexcept                             { return (mp); }
        
        T* const release() noexcept                                         { auto p = mp; mp = nullptr; return p; }
        void reset(T* p = nullptr) noexcept                                 { auto d = mp; mp = p; if (d){ d->~T(); } }
        void swap(local_ptr<T>& Swap) noexcept                              { auto p = mp; mp = Swap.mp; Swap.mp = p; }
        T* const get() const noexcept                                       { return mp; }
    
    private:
        local_ptr(const local_ptr<T>& rhs) noexcept                         = delete;
        local_ptr<T>& operator =(const local_ptr<T>& rhs) noexcept          = delete;
    
    private:
        T* mp;
};
