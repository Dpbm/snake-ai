#include "exceptions.h"


namespace Utils {

  FileNotFound::FileNotFound(){}
  
  const char* FileNotFound::what() const throw(){
    return "File Not Found!";
  }
 


  InvalidValues::InvalidValues(){}
  
  const char* InvalidValues::what() const throw(){
    return "You haven't set the intern class values before doing the operation!";
  }

}
