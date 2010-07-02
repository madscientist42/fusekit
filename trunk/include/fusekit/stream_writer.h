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

#ifndef __FUX__STREAM_WRITER_H
#define __FUX__STREAM_WRITER_H

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
