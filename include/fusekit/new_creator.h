
#ifndef __FUSEKIT__NEW_CREATOR_H
#define __FUSEKIT__NEW_CREATOR_H

#include <fusekit/entry.h>

namespace fusekit{

  template< class T >
  struct new_creator{
    T* operator()(){
      return new T;
    }
  };

}

#endif


