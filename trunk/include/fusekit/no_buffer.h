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

#ifndef __FUSEKIT__NO_BUFFER_H
#define __FUSEKIT__NO_BUFFER_H

#include <fusekit/entry.h>

namespace fusekit{

  template< 
    class Derived 
    >
  struct no_buffer {

    int open( fuse_file_info& ){
      return -EISDIR;
    }

    int close( fuse_file_info& ){
      return -EISDIR;
    }

    int size(){
      return 0;
    }

    int read( char*, size_t, off_t, fuse_file_info& ){      
      return -EISDIR;
    }

    int write( const char*, size_t, off_t, fuse_file_info& ){
      return -EISDIR;
    }

    int flush( fuse_file_info& ) {
      return -EISDIR;
    }

    int truncate( off_t offset ) {
      return -EISDIR;
    }    
  };

}

#endif


