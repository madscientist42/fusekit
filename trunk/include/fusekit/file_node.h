
#ifndef __FUSEKIT__FILE_NODE_H
#define __FUSEKIT__FILE_NODE_H

#include <fusekit/entry.h>

namespace fusekit{

  template<
    class Derived
    >
  struct file_node {

    static const int type_flag = S_IFREG;

    typedef file_node node;

    entry* find( const char* ){
      return 0;
    }
    
    int links(){
      return 1;
    }

    int readdir( void*, fuse_fill_dir_t, off_t, fuse_file_info& ){
      return -ENOTDIR;
    }

    int mknod( const char* name, mode_t mode, dev_t type){
      return -ENOTDIR;
    }

    int unlink( const char* name ){
      return -ENOTDIR;
    }

    int mkdir( const char* name, mode_t mode ){
      return -ENOTDIR;
    }

    int rmdir( const char* name ){
      return -ENOTDIR;
    }
  };
}

#endif


