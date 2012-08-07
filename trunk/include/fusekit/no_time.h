
#ifndef __FUSEKIT__NO_TIME_H
#define __FUSEKIT__NO_TIME_H

#include <time.h>

namespace fusekit{

  template<
    class Derived
    >
  struct no_time {
    time_t modification_time() {
      return 0;
    }

    time_t change_time() {
      return 0;
    }

    time_t access_time() {
      return 0;
    }

    void update( int ) {
    }
  };

}

#endif


