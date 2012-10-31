
#ifndef __FUSEKIT__TYPE_READER_H
#define __FUSEKIT__TYPE_READER_H

#include <error.h>
#include <iostream>
#include <ostream>

namespace fusekit{
  template< class T  >
  struct type_reader {
    type_reader() 
      : _t(0) {
    }
    type_reader( T& t ) 
      : _t(&t) {
    }
    int operator()( std::ostream& os ){
      os << (*_t);    
      if( !os.good() ){
	return -EIO;
      }
      return 0;
    }
  private:
    T* _t;
  };
}

#endif
