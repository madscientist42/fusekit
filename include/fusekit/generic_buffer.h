
#ifndef __FUSEKIT__GENERIC_BUFFER_H
#define __FUSEKIT__GENERIC_BUFFER_H

#include <error.h>
#include <fcntl.h>
#include <fusekit/entry.h>
#include <fusekit/file_handle.h>
#include <fusekit/time_fields.h>

namespace fusekit{
  template< 
    class Reader,
    class Writer,
    int MaxSize,
    class Derived
    >
  struct generic_buffer{

    struct file_handle : ::fusekit::file_handle {
      file_handle() 
	: last_read_err(-1)
	, last_write_err(-1){
      }
      Reader reader;
      Writer writer;
      int last_read_err;
      int last_write_err;
    };

    void init_reader( Reader& r ){
      _reader = r;
    }

    void init_writer( Writer& w ){
      _writer = w;
    }


    static bool write_flag_set( int flags ){
      int accmode = flags & O_ACCMODE;
      if( accmode == O_WRONLY || accmode == O_RDWR ){
	return true;
      }
      return false;
    }

    static bool read_flag_set( int flags ){
      int accmode = flags & O_ACCMODE;
      if( accmode == O_RDONLY || accmode == O_RDWR ){
	return true;
      }
      return false;
    }

    int open( fuse_file_info& fi ){
      file_handle* fh = new file_handle;
      fi.fh = reinterpret_cast< uint64_t >(fh);
      if( read_flag_set(fi.flags) ){
	fh->reader = _reader;
      }
      if( write_flag_set(fi.flags) ){
	fh->writer = _writer;
      }
      return 0;
    }

    int close( fuse_file_info& fi ){
      if( fi.fh == 0 ){
	return -EBADF;
      }
      file_handle* fh = reinterpret_cast< file_handle* >(fi.fh);
      if( fh->last_read_err >= 0){
	static_cast< Derived* >(this)->update( access_time );
      }
      if( fh->last_write_err >= 0){
	static_cast< Derived* >(this)->update( modification_time );
      }
      delete fh;
      fi.fh = 0;
      return 0;
    }

    int read( char* buf, size_t size, off_t offset, fuse_file_info& fi ){   
      if( fi.fh == 0 ){
	return -EBADF;
      }
      file_handle* fh = reinterpret_cast< file_handle* >(fi.fh);
      fh->last_read_err = fh->reader(buf,size,offset);
      return fh->last_read_err;
    }

    int write( const char* buf, size_t size, off_t offset, fuse_file_info& fi){
      if( fi.fh == 0 ){
	return -EBADF;
      }
      file_handle* fh = reinterpret_cast< file_handle* >(fi.fh);
      fh->last_write_err = fh->writer(buf,size,offset);
      return fh->last_write_err;
    }

    int size(){
      return MaxSize;
    }

    int flush( fuse_file_info& fi) {
      if( fi.fh == 0 ){
	return -EBADF;
      }
      return 0;
    }

    int truncate( off_t offset ) {
      return offset;
    }    

  private:
    Reader _reader;
    Writer _writer;
  };
}

#endif
