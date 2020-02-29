#ifndef _UTILS_INCLUDE_
#define _UTILS_INCLUDE_

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cerrno>
#include <fstream>

#define MAXERROR 126

class Utils
{
   public:
      void error(std::string merror, int error_num);
      bool file_exist(std::string fname);
      bool file_empty(std::string fname);
};
#endif
