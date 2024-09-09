#ifndef HW2_EXCEPTION_H
#define HW2_EXCEPTION_H

#include <exception>

class Failure: public std::exception{};
class InvalidInput: public std::exception{};
class AllocationError: public std::exception{};

#endif //HW2_EXCEPTION_H