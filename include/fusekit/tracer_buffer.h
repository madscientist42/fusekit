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
