
#ifndef __FUSEKIT__TYPE_WRITER_H
#define __FUSEKIT__TYPE_WRITER_H

#include <error.h>
#include <istream>

namespace fusekit{
  template< class T  >
  struct type_writer {
    type_writer() 
      : _t(0) {
    }

    type_writer( T& t ) 
      : _t(&t) {
    }
    int operator()( std::istream& is ){
      is >>(*_t);     
      if( is.bad() || is.fail() ){
	return -EIO;
      }
      return 0;
    }
  private:
    T* _t;
  };
}
#endif
