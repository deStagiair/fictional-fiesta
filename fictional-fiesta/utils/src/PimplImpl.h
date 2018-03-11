#ifndef INCLUDE_FICTIONAL_FIESTA_UTILS_PIMPL_IMPL_H
#define INCLUDE_FICTIONAL_FIESTA_UTILS_PIMPL_IMPL_H

#include <utility>

namespace fictionalfiesta
{

template <typename T>
Pimpl<T>::Pimpl():
  _pointer{new T{}}
{
}

template <typename T>
template <typename ...Args>
Pimpl<T>::Pimpl(Args&& ...args):
  _pointer{new T{std::forward<Args>(args)...}}
{
}

template <typename T>
//Pimpl<T>::~Pimpl() = default;
Pimpl<T>::~Pimpl()
{
}

template<typename T>
T* Pimpl<T>::operator->()
{
  return _pointer.get();
}

template<typename T>
const T* Pimpl<T>::operator->() const
{
  return _pointer.get();
}

template<typename T>
T& Pimpl<T>::operator*()
{
  return *_pointer;
}

template<typename T>
const T& Pimpl<T>::operator*() const
{
  return *_pointer;
}

} // namespace fictionalfiesta

#endif
