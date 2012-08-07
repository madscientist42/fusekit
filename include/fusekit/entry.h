
#ifndef __FUSEKIT__ENTRY_H
#define __FUSEKIT__ENTRY_H

#include <errno.h>
#include <string>
#include <fuse.h>

namespace fusekit{

  /// interface base class for all entries/elements of a file hierarchy
  /// 
  /// all file operations will be forwarded by the daemon to an implementation
  /// of this interface.
  struct entry{
    virtual ~entry(){
    }
    virtual entry* child( const char* ) = 0;
    virtual int stat( struct stat& ) = 0;
    virtual int access( int ) = 0;
    virtual int chmod( mode_t ) = 0;
    virtual int open( fuse_file_info& ) = 0;
    virtual int release( fuse_file_info& ) = 0;
    virtual int read( char*, size_t, off_t, fuse_file_info& ) = 0;
    virtual int write( const char*, size_t, off_t, fuse_file_info& ) = 0;
    virtual int readdir( void*, fuse_fill_dir_t, off_t, fuse_file_info& ) = 0;
    virtual int mknod( const char*, mode_t, dev_t ) = 0;
    virtual int unlink( const char* ) = 0;
    virtual int mkdir( const char*, mode_t ) = 0;
    virtual int rmdir( const char* ) = 0;
    virtual int flush( fuse_file_info& ) = 0;
    virtual int truncate( off_t ) = 0;
    virtual int utime( utimbuf& ) = 0;
  };
}

#endif


