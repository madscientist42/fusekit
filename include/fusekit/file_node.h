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

#ifndef __FUSEKIT__FILE_NODE_H
#define __FUSEKIT__FILE_NODE_H

#include <fusekit/entry.h>

namespace fusekit{

  template<
    class Derived
    >
  struct file_node {

    static const int type_flag = S_IFREG;

    typedef file_node node;

    entry* find( const char* ){
      return 0;
    }
    
    int links(){
      return 1;
    }

    int readdir( void*, fuse_fill_dir_t, off_t, fuse_file_info& ){
      return -ENOTDIR;
    }

    int mknod( const char* name, mode_t mode, dev_t type){
      return -ENOTDIR;
    }

    int unlink( const char* name ){
      return -ENOTDIR;
    }

    int mkdir( const char* name, mode_t mode ){
      return -ENOTDIR;
    }

    int rmdir( const char* name ){
      return -ENOTDIR;
    }
  };
}

#endif


