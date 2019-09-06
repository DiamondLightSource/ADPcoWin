#include "NDArrayException.h"
#include <sstream>

/**
 * Constructor
 * \param[in] reason The reason during which the exception was raised
 */
NDArrayException::NDArrayException(const char* reason)
    : reason(reason)
{
    std::stringstream s;
    s << "NDArray allocation error during " << this->reason << std::endl;
    this->text = s.str();
}

/**
 * Destructor.
 */
NDArrayException::~NDArrayException() throw()
{
}

/**
 * Return a string representation of the exception
 */
const char* NDArrayException::what() const throw()
{
  return text.c_str();
}

