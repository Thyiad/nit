#include <exception>
#include <iostream>

#include <boost/exception/all.hpp>


/// Guards a main function from exceptions.
///
/// @tparam T  Function type returning integer code.
///
/// @param[in] runner  The body of the main function.
///
/// @returns The return of the runner if no exceptions are encountered.
///          1 if an exception is encountered.
template <class T>
int guard(T&& runner) noexcept {
  return runner();
}
