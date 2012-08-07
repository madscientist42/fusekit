
#ifndef __FUSEKIT__NO_BUFFER_H
#define __FUSEKIT__NO_BUFFER_H

#include <fusekit/entry.h>

namespace fusekit{

  template< 
    class Derived 
    >
  struct no_buffer {

    int open( fuse_file_info& ){
      return -EISDIR;
    }

    int close( fuse_file_info& ){
      return -EISDIR;
    }

    int size(){
      return 0;
    }

    int read( char*, size_t, off_t, fuse_file_info& ){      
      return -EISDIR;
    }

    int write( const char*, size_t, off_t, fuse_file_info& ){
      return -EISDIR;
    }

    int flush( fuse_file_info& ) {
      return -EISDIR;
    }

    int truncate( off_t offset ) {
      return -EISDIR;
    }    
  };

}

#endif


