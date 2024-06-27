#pragma once

#include <exception>
#include <stdexcept>

using std::exception;

namespace Utils {
  
  class FileNotFound : public exception{ 
    public:
      FileNotFound();
      const char* what() const throw();
  };
  
  class InvalidValues : public exception{ 
    public:
      InvalidValues();
      const char* what() const throw();
  };

};
