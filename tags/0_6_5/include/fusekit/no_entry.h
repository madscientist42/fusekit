
#ifndef __FUSEKIT__NO_ENTRY_H
#define __FUSEKIT__NO_ENTRY_H

#include <fusekit/entry.h>

namespace fusekit{

  /// a fallback entry implementation (only used by the daemon).
  /// 
  /// if the daemon does not find an entry specified by the input path,
  /// this class is used as fallback.
  struct no_entry : entry{
    virtual entry* child( const char* ){
      return 0;
    }
    virtual int stat( struct stat& ){
      return -ENOENT;
    }
    virtual int access( int ){
      return -ENOENT;
    }
    virtual int chmod( mode_t ){
      return -ENOENT;
    }
    virtual int open( fuse_file_info& ){
      return -ENOENT;
    }
    virtual int release( fuse_file_info& ){
      return -ENOENT;
    }
    virtual int read( char*, size_t, off_t, fuse_file_info& ){
      return -ENOENT;
    }
    virtual int write( const char*, size_t, off_t, fuse_file_info& ){
      return -ENOENT;
    }
    virtual int readdir( void*, fuse_fill_dir_t, off_t, fuse_file_info& ){
      return -ENOENT;
    }
    virtual int mknod( const char*, mode_t, dev_t ){
      return -ENOENT;
    }
    virtual int unlink( const char* ){
      return -ENOENT;
    }
    virtual int mkdir( const char*, mode_t ){
      return -ENOENT;
    }
    virtual int rmdir( const char* ){
      return -ENOENT;
    }
    virtual int flush( fuse_file_info& ){ 
      return -ENOENT; 
    }
    virtual int truncate( off_t ){ 
      return 0; 
    }
    virtual int utime( utimbuf& ){
      return -ENOENT;
    }
  };
}

#endif


