#ifndef INCLUDE_FICTIONAL_FIESTA_UTILS_PIMPL_H
#define INCLUDE_FICTIONAL_FIESTA_UTILS_PIMPL_H

#include <memory>

namespace fictionalfiesta
{

/// @brief Helper class to implement the PIMPL (pointer to implementation) idiom.
/// Based in GOTW #101 by Herb Sutter.
template <typename T>
class Pimpl
{
  private:

    /// Pointer to the implementation instance.
    std::unique_ptr<T> _pointer;

  public:

    /// @brief Default constructor.
    Pimpl();

    template<typename ...Args>
    Pimpl(Args&& ...);

    ~Pimpl();

    T* operator->();
    const T* operator->() const;
    T& operator*();
    const T& operator*() const;
};

} // namespace fictionalfiesta

#endif
