#include "utils.hpp"

void Utils :: error(std::string merror, int error_num)
{
   char buffer[MAXERROR];
         
   snprintf(buffer, MAXERROR-1,"\n%s\n", merror.c_str());
   std::cout<<buffer;
   if (errno > 0)
   {
      snprintf(buffer, MAXERROR-1,"Err num (hex)= %x\n", error_num);
      std::cout<<buffer;
   }
}

bool Utils :: file_exist(std::string fname)
{
   std::ifstream file(fname.c_str());
      return file.good();
}
   
bool Utils :: file_empty(std::string fname)
{
   char byte;
   bool flag = true;
   FILE *fptr = fopen(fname.c_str(), "r");

   if (fptr != NULL)
   {
      if(fscanf(fptr,"%c",&byte) != EOF)
         flag = false;
    
      fclose(fptr);
   }

   return flag;
}
