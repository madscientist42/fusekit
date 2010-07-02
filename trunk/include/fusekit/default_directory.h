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

#ifndef __FUX__DEFAULT_DIRECTORY_H
#define __FUX__DEFAULT_DIRECTORY_H

#include <fusekit/basic_directory.h>
#include <fusekit/directory_node.h>
#include <fusekit/directory_factory.h>
#include <fusekit/file_factory.h>


namespace fusekit{

  template<
    class DirectoryFactory = directory_factory<>,
    class FileFactory = file_factory<>
    >
  struct default_directory {
    template<
      class Derived
      >
    struct directory_node_alias : 
      public directory_node< 
      DirectoryFactory,
      FileFactory,
      Derived
      >{
    };
    typedef basic_directory< directory_node_alias > type;
  };

  inline
  default_directory<>::type* make_default_directory(){
    return new default_directory<>::type;
  }
  
}

#endif


