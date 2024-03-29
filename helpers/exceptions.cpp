#include "exceptions.h"


namespace Utils {

  FileNotFound::FileNotFound(){}
  
  const char* FileNotFound::what() const throw(){
    return "File Not Found!";
  }

}
