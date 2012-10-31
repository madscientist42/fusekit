
#ifndef __FUSEKIT__TRACER_BUFFER_H
#define __FUSEKIT__TRACER_BUFFER_H

#include <iostream>
#include <fusekit/entry.h>

namespace fusekit{
  template< 
    class Derived 
    >
  struct tracer_buffer {
    
    tracer_buffer() : _os( std::cout ){
      _os << "tracer_buffer::tracer_buffer()" << std::endl;
    }

    void set_ostream( std::ostream& os ) {
      _os = os;
    }

    ~tracer_buffer(){
      _os << "tracer_buffer::~tracer_buffer()" << std::endl;
    }

    int open( fuse_file_info& ){
      _os << "tracer_buffer::open(...)" << std::endl;
      return 0;
    }

    int close( fuse_file_info& ){
      _os << "tracer_buffer::close(...)" << std::endl;
      return 0;
    }

    int size(){
      _os << "tracer_buffer::size(...)" << std::endl;
      return 0;
    }

    int read( char* buf, size_t size, off_t offset, fuse_file_info& ){   
      _os << "tracer_buffer::read(...)" << std::endl;
      return 0;
    }

    int write( const char*, size_t, off_t, fuse_file_info& ){
      _os << "tracer_buffer::write(...)" << std::endl;
      return 0;
    }

    int flush( fuse_file_info& ) {
      _os << "tracer_buffer::flush(...)" << std::endl;
      return 0;
    }

    int truncate( off_t offset ) {
      _os << "tracer_buffer::truncate(...)" << std::endl;
      return offset;
    }    
  private:
    std::ostream&_os;
  };
}

#endif
