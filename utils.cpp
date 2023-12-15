#include <cstdlib>
#include <ctime>
#include "utils.h"

namespace Utils {
  unsigned int random(unsigned int start,  unsigned int end){
    srand(time(NULL));
    return rand() % end + start;
  }
}
