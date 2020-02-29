#include "utils.hpp"
#include "kmeans.hpp"

int main(int argc, char *argv[])
{
   Utils helper;

   // step1) check for syntax error
   if (argc != 2)
   {
      helper.error("Usage: ./kmeans <full_path_of_the_input_file.txt>", errno);
      exit(0);     
   }

   // step2) check whether the input data file exist or not
   // csv file is expected
   std::string fname = argv[1];
   if (helper.file_exist(fname) == false)
   {
      // file does not exist
      char buffer[MAXERROR];
      sprintf(buffer, "%s does not exist", fname.c_str());
      helper.error(buffer, errno);
      exit(0);     
   }

   // step3) check the input data fle is not empty
   if (helper.file_empty(fname) == true)
   {
      // file does not exist
      char buffer[MAXERROR];
      sprintf(buffer, "%s is either empty or does not have read permission", fname.c_str());
      helper.error(buffer, errno);
      exit(0);
   }

   // step4) execute the kmeans algorithm
   Kmeans algrithm;
   if (algrithm.execute_kmeans_algorithm(fname) == false)  // this will write the result into output.txt file in curr dir
   {
      // file does not exist
      char buffer[MAXERROR];
      sprintf(buffer, "Cannot execute kmeans algorithm on this file = %s", fname.c_str());
      helper.error(buffer, errno);
      exit(0);
   }

   // step5) print the result
   algrithm.print_result("./output.txt");
}
