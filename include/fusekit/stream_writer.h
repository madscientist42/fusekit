
#ifndef __FUSEKIT__STREAM_WRITER_H
#define __FUSEKIT__STREAM_WRITER_H

#include <error.h>
#include <sstream>
#include <algorithm>
#include <fusekit/entry.h>


namespace fusekit{

  template< class Writer, char Delimiter >
  struct stream_writer {

    stream_writer( Writer& w )
      : _writer(w)
      , _err(0){
    }

    stream_writer()
      : _err(0){
    }

    stream_writer( const stream_writer& other ){
      operator=( other );
    }

    stream_writer& operator=( const stream_writer& other ){
      _writer = other._writer;
      _err = 0;
      return *this;
    }

    int operator()( const char* buf, size_t size, off_t offset ){
      const char* end = std::find( buf, buf+size, Delimiter );
      if( _is.tellp() ){
	_is.seekp( offset );
      } 
      // if delimiter has been found, end is buf+size-1,
      // thus the range does not include the delimiter
      _is.write( buf, end - buf );
      if( !_is.good() ){
	return -EINVAL;
      }
      if( end != (buf+size) ){
	_err = _writer( _is );
	if( _err != 0 ){
	  return _err;
	}
      }
      return size;
    }

  private:
    std::stringstream _is;
    Writer _writer;
    int _err;
  };
}

#endif
