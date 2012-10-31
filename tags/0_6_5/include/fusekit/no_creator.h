
#ifndef __FUSEKIT__NO_CREATOR_H
#define __FUSEKIT__NO_CREATOR_H

#include <fusekit/entry.h>

namespace fusekit{

  struct no_creator{
    entry* operator()(){
      return 0;
    }
  };

}

#endif


