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

#ifndef __FUSEKIT__PATH_H_
#define __FUSEKIT__PATH_H_

#include <list>
#include <string>
#include <sstream>

namespace fusekit{
  struct path : public std::list< std::string >{
    inline
    path( const char* path_str ){
      std::istringstream ps(path_str+1); //skip leading /
      char token[256];
      std::list< std::string > parts;
      while( ps.getline(token,256,'/') ){
	push_back(token);
      }
    }
  };
}

#endif
