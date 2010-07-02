/*
 * This file is part of fusekit, a c++ convenience wrapper for FUSE.
 *
 * Written by Gerhard Lipp <gerhard_lipp@gmx.de>
 *
 * this library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with fusekit.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __FUX__STREAM_READER_H
#define __FUX__STREAM_READER_H

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
