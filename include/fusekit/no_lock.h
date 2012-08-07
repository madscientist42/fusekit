
#ifndef __FUSEKIT__NO_LOCK_H
#define __FUSEKIT__NO_LOCK_H

namespace fusekit{
  struct no_lock {
    struct lock{
      lock( no_lock& ){
      }
    };
  };
}

#endif


