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

#ifndef __FUX__DEFAULT_TIME_H
#define __FUX__DEFAULT_TIME_H

#include <time.h>
#include <fusekit/time_fields.h>

namespace fusekit{

  template<
    class Derived
    >
  struct default_time {

    default_time() : 
      _change_time( ::time(NULL) ),
      _modification_time( _change_time ),
      _access_time( _change_time ) {
    }
	 
    time_t modification_time() {
      return _modification_time;
    }

    time_t change_time() {
      return _change_time;
    }

    time_t access_time() {
      return _access_time;
    }

    void update( int mask ){
      const time_t now(::time(NULL));
      if( mask & fusekit::change_time ) {
	_change_time = now;
      }
      if( mask & fusekit::modification_time ) {
	_modification_time = now;
      }
      if( mask & fusekit::access_time ) {
	_access_time = now;
      }
    }

  private:
    time_t _change_time;
    time_t _modification_time;
    time_t _access_time;
  };
}

#endif


