#include "kmeans.hpp"

// This function calls the python script and execute the kmeans algorithm
bool Kmeans :: execute_kmeans_algorithm(std::string fname)
{
   std::string script_name = " /home/user/Nasa/TensorFlow/KMEANS/kmeans.py "; // ensure it starts with a space and ends with a space
   std::string command = "python";
   command += script_name;
   command += fname;
   system(command.c_str());

   return true;
}
 
// This function prints the output of the kmeans algorithm .
// The output only contains the centroid
void Kmeans :: print_result(std::string fname)
{
   std::ifstream file(fname.c_str());
   if (file.is_open()) 
   {
      std::string line;
      while (getline(file, line))
         fprintf(stdout, "%s", line.c_str());
      std::cout<<std::endl;
      file.close();
   }
}    
