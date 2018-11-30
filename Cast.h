#pragma once



template <class T>  constexpr T* const_off(const T* p) noexcept     { return const_cast<T*>(p); }

template <class T, class S> constexpr T* to_ptr(const S* p)         { return reinterpret_cast<T*>(const_off(p)); }
