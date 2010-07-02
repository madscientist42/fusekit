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

#ifndef __FUX__STREAM_FUNCTION_FILE_H
#define __FUX__STREAM_FUNCTION_FILE_H

#include <tr1/functional>
#include <fusekit/stream_callback_file.h>

namespace fusekit {

  template< 
    int MaxSize = 4096,
    char Delimiter = '\n',
    template <class> class TimePolicy = default_time,
    template <class> class PermissionPolicy = default_ro_file_permissions
    >
  struct ostream_function_file 
    : public ostream_callback_file< 
    std::tr1::function< int (std::ostream&) >,
    MaxSize,
    Delimiter,
    TimePolicy,
    PermissionPolicy
    >::type {
    ostream_function_file( std::tr1::function< int (std::ostream&) > rcb) : ostream_callback_file< 
      std::tr1::function< int (std::ostream&) >,
      MaxSize,
      Delimiter,
      TimePolicy,
      PermissionPolicy
      >::type( rcb ){
    }
  };

  inline
  ostream_function_file<>*
  make_ostream_function_file(  std::tr1::function< int (std::ostream&) > readcb ){
    return new ostream_function_file<>(readcb);
  }

  template< 
    int MaxSize = 4096,
    char Delimiter = '\n',
    template <class> class TimePolicy = default_time,
    template <class> class PermissionPolicy = default_wo_file_permissions
    >
  struct istream_function_file 
    : public istream_callback_file< 
    std::tr1::function< int (std::istream&) >,
    MaxSize,
    Delimiter,
    TimePolicy,
    PermissionPolicy
    >::type {
    istream_function_file( std::tr1::function< int (std::istream&) > wcb) : istream_callback_file< 
      std::tr1::function< int (std::istream&) >,
      MaxSize,
      Delimiter,
      TimePolicy,
      PermissionPolicy
      >::type( wcb ){
    }
  };

  inline
  istream_function_file<>*
  make_istream_function_file(  std::tr1::function< int (std::istream&) > writecb ){
    return new istream_function_file<>(writecb);
  }

  template< 
    int MaxSize = 4096,
    char Delimiter = '\n',
    template <class> class TimePolicy = default_time,
    template <class> class PermissionPolicy = default_file_permissions
    >
  struct iostream_function_file 
    : public iostream_callback_file< 
    std::tr1::function< int (std::ostream&) >,
    std::tr1::function< int (std::istream&) >,
    MaxSize,
    Delimiter,
    TimePolicy,
    PermissionPolicy
    >::type {

    iostream_function_file( 
			   std::tr1::function< int (std::ostream&) > rcb, 
			   std::tr1::function< int (std::istream&) > wcb
			    ) : iostream_callback_file< 
      std::tr1::function< int (std::ostream&) >,
      std::tr1::function< int (std::istream&) >,
      MaxSize,
      Delimiter,
      TimePolicy,
      PermissionPolicy
      >::type( rcb,wcb ){
    }
  };
  
  inline
  iostream_function_file<>*
  make_iostream_function_file( std::tr1::function< int (std::ostream&) > readcb,  std::tr1::function< int (std::istream&) > writecb ){
    return new iostream_function_file<>(readcb,writecb);
  }
}
  
#endif

