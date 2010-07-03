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

#ifndef __FUSEKIT__DEFAULT_PERMISSIONS_H
#define __FUSEKIT__DEFAULT_PERMISSIONS_H

#include <fusekit/entry.h>

namespace fusekit{

  template< 
    mode_t Permissions,
    class Derived
    >
  struct default_permissions {

    default_permissions()
      : _current( Permissions ){
    }

    int access( int permissions ){
      if( permissions & (~_current) )
	return -EACCES;
      return 0;
    }
  
    int chmod( mode_t permissions ){
      static_cast< Derived* >(this)->update(fusekit::modification_time);
      _current = permissions;
      return 0;
    }

    int mode() {
      return _current;
    }

  private:
    int _current;
  };

  template<
    class Derived
    >
  struct default_file_permissions 
    : public default_permissions< 0666, Derived >{
  };

  template<
    class Derived
    >
  struct default_ro_file_permissions 
    : public default_permissions< 0444, Derived >{
  };

  template<
    class Derived
    >
  struct default_wo_file_permissions 
    : public default_permissions< 0222, Derived >{
  };

  template<
    class Derived
    >
  struct default_directory_permissions 
    : public default_permissions< 0755, Derived >{
  };
}

#endif


