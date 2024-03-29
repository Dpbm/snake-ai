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

};
