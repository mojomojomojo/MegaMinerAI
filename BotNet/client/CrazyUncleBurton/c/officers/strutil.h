#ifndef __STRUTIL__
#define __STRUTIL__

#include <string>
#include <sstream>

#define INT_T_STR(inttype)                                 \
  inline std::string inttype ## _str( inttype i ) {        \
    std::stringstream s(std::stringstream::out);        \
    s << i;                                             \
    return s.str();                                     \
  }

INT_T_STR(int16_t)

INT_T_STR(int)

#endif // __STRUTIL__
