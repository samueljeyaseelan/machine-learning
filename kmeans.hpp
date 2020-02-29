#ifndef _KMEANS_INCLUDE_
#define _KMEANS_INCLUDE_

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cerrno>
#include <fstream>

class Kmeans
{
   public:
      bool execute_kmeans_algorithm(std::string fname);
      void print_result(std::string fname);
};

#endif
