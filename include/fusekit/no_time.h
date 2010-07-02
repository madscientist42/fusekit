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

#ifndef __FUX__NO_TIME_H
#define __FUX__NO_TIME_H

#include <time.h>

namespace fusekit{

  template<
    class Derived
    >
  struct no_time {
    time_t modification_time() {
      return 0;
    }

    time_t change_time() {
      return 0;
    }

    time_t access_time() {
      return 0;
    }

    void update( int ) {
    }
  };

}

#endif


