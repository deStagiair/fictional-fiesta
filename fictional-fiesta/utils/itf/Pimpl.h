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

    /// @brief Move constructor.
    Pimpl(Pimpl&&);

    /// @brief Forward constructor.
    /// Construct directly the underlaying class from the corresponding arguments.
    /// @param args Arguments to be forwarded to the underlaying class constructor.
    template<typename ...Args>
    Pimpl(Args&& ...args);

    ~Pimpl();

    /// @brief Arrow derreference operator.
    /// @return pointer to the internal member.
    /// @{
    T* operator->();
    const T* operator->() const;
    /// @}

    /// @brief Star derreference operator.
    /// @return reference to the internal member.
    /// @{
    T& operator*();
    const T& operator*() const;
    /// @}
};

} // namespace fictionalfiesta

#endif
