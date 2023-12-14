#include <cstdlib>
#include <ctime>


namespace Utils {
  unsigned int random(unsigned int start,  unsigned int end){
    srand(time(NULL));
    return rand() % end + start;
  }
}
