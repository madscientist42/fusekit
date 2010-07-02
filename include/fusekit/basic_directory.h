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

#ifndef __FUX__BASIC_DIRECTORY_H
#define __FUX__BASIC_DIRECTORY_H

#include <fusekit/basic_entry.h>
#include <fusekit/no_buffer.h>
#include <fusekit/default_time.h>
#include <fusekit/default_permissions.h>

namespace fusekit{
  template<
    template <class> class NodePolicy, 
    template <class> class TimePolicy = default_time,
    template <class> class PermissionPolicy = default_directory_permissions
    >
  struct basic_directory
    : public basic_entry<
    TimePolicy,
    PermissionPolicy,
    no_buffer,
    NodePolicy,
    S_IFDIR
    >{
  };
}

#endif


