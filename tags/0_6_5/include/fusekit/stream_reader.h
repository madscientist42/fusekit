
#ifndef __FUSEKIT__STREAM_READER_H
#define __FUSEKIT__STREAM_READER_H

#include <error.h>
#include <iostream>
#include <fusekit/entry.h>

namespace fusekit{
  template< class Reader, char Delimiter >
  struct stream_reader {

    stream_reader( Reader& w )
      : _reader(w)
      , _err(0){
    }

    stream_reader()
      : _err(0){
    }

    stream_reader( const stream_reader& other ){
      operator=( other );
    }

    stream_reader& operator=( const stream_reader& other ){
      _reader = other._reader;
      _err = 0;
      return *this;
    }

    int operator()( char* buf, size_t size, off_t offset){
      if( offset == 0 ){
	if( _os.tellp() ){
	  _os.seekp(0);
	}
	_err = _reader( _os );
	_os << Delimiter;
	_os.flush();
      }
      
      if( _err != 0 ){
	return _err;
      }
      else{
	_os.seekg( offset );
	return _os.readsome( buf, size );
      }
    }
  private:
    std::stringstream _os;
    Reader _reader;
    int _err;
  };

}

#endif
