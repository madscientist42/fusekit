
#ifndef __FUSEKIT__BASIC_ENTRY_H
#define __FUSEKIT__BASIC_ENTRY_H

#include <fusekit/entry.h>
#include <fusekit/time_fields.h>

namespace fusekit{
  
  /// the template host class for file entries, which follows the so called 
  /// "Curiously Recurring Template Pattern" described in ....
  /// compile time polymorphism.
  ///
  ///
  template< 
    template <class> class TimePolicy,
    template <class> class PermissionPolicy,
    template <class> class BufferPolicy,
    template <class> class NodePolicy,
    int TypeFlag
    >
  struct basic_entry 
    : public entry
    , public TimePolicy< basic_entry< TimePolicy, PermissionPolicy, BufferPolicy, NodePolicy, TypeFlag > >
    , public PermissionPolicy< basic_entry< TimePolicy, PermissionPolicy, BufferPolicy, NodePolicy, TypeFlag > >
    , public BufferPolicy< basic_entry< TimePolicy, PermissionPolicy, BufferPolicy, NodePolicy, TypeFlag > >
    , public NodePolicy< basic_entry< TimePolicy, PermissionPolicy, BufferPolicy, NodePolicy, TypeFlag > >{

    template< template <class> class Base >
    inline 
    Base< basic_entry< TimePolicy, PermissionPolicy, BufferPolicy, NodePolicy, TypeFlag > >& base() {
      return static_cast< Base< basic_entry< TimePolicy, PermissionPolicy, BufferPolicy, NodePolicy, TypeFlag > >& >(*this);
    }

    virtual entry* child( const char* name ){
      return base< NodePolicy >().find( name );
    }

    virtual int stat( struct stat& stbuf){
      stbuf.st_mode = TypeFlag | base< PermissionPolicy >().mode();
      stbuf.st_nlink = base< NodePolicy >().links();
      stbuf.st_size = base< BufferPolicy >().size();
      stbuf.st_ctime = base< TimePolicy >().change_time();
      stbuf.st_atime = base< TimePolicy >().access_time();
      stbuf.st_mtime = base< TimePolicy >().modification_time();
      return 0;
    }

    virtual int access( int mode ){
      return base< PermissionPolicy >().access( mode );
    }

    virtual int chmod( mode_t permission ){
      return base< PermissionPolicy >().chmod( permission );
    }

    virtual int open( fuse_file_info& fi ){
      return base< BufferPolicy >().open(fi);
    }

    virtual int release( fuse_file_info& fi ){
      return base< BufferPolicy >().close(fi);
    }

    virtual int read( char* buf, size_t size, off_t offset, fuse_file_info& fi ){      
      return base< BufferPolicy >().read( buf, size, offset, fi );
    }

    virtual int write( const char* buf, size_t size, off_t offset, fuse_file_info& fi ){
      return base< BufferPolicy >().write( buf, size, offset, fi );
    }

    virtual int readdir( void *buf, fuse_fill_dir_t filler, off_t offset, fuse_file_info& fi){
      return base< NodePolicy >().readdir( buf, filler, offset, fi );
    }

    virtual int mknod( const char* name, mode_t mode, dev_t type){
      return base< NodePolicy >().mknod( name, mode, type );
    }

    virtual int unlink( const char* name ){
      return base< NodePolicy >().unlink( name );
    }

    virtual int mkdir( const char* name, mode_t mode ){
      return base< NodePolicy >().mkdir( name, mode );
    }

    virtual int rmdir( const char* name ){
      return base< NodePolicy >().rmdir( name );
    }

    virtual int flush( fuse_file_info& fi ){ 
      return base< BufferPolicy >().flush( fi );
    }

    virtual int truncate( off_t off ){ 
      return base< BufferPolicy >().truncate( off );
    }

    virtual int utime( utimbuf& ){
      base< TimePolicy >().update( fusekit::access_time | fusekit::modification_time );
      return 0;
    }
  };
}

#endif


