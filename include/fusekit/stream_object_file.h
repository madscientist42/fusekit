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

#ifndef __FUSEKIT__STREAM_OBJECT_FILE_H
#define __FUSEKIT__STREAM_OBJECT_FILE_H

#include <sstream>
#include <fusekit/basic_file.h>
#include <fusekit/no_stream_reader.h>
#include <fusekit/no_stream_writer.h>
#include <fusekit/stream_reader.h>
#include <fusekit/stream_writer.h>
#include <fusekit/type_reader.h>
#include <fusekit/type_writer.h>
#include <fusekit/generic_buffer.h>

namespace fusekit {

  template< 
    class StreamableType,
    char Delimiter = '\n',
    int MaxSize = 4096,
    template <class> class TimePolicy = default_time,
    template <class> class PermissionPolicy = default_ro_file_permissions
    >
  struct ostream_object_file{
    template<
      class Derived
      >
    struct ostream_object_buffer_alias 
      : public generic_buffer< 
      stream_reader< type_reader< StreamableType >, Delimiter >, 
      no_stream_writer, 
      MaxSize, 
      Derived > {
    };

    struct type 
      : public basic_file< ostream_object_buffer_alias, TimePolicy, PermissionPolicy >{
      type( StreamableType& so ) {
	type_reader< StreamableType > r(so);
	stream_reader< type_reader< StreamableType >, Delimiter > rr(r);
	this->init_reader(rr);
      }      
    }; 
  };

  template< class StreamableType > 
  typename ostream_object_file< StreamableType >::type*
  make_ostream_object_file( StreamableType& so ){
    return new typename ostream_object_file< StreamableType >::type(so);
  }


  template< 
    class StreamableType,
    char Delimiter = '\n',
    int MaxSize = 4096,
    template <class> class TimePolicy = default_time,
    template <class> class PermissionPolicy = default_wo_file_permissions
    >
  struct istream_object_file{
    template<
      class Derived
      >
    struct istream_object_buffer_alias 
      : public generic_buffer< 
      no_stream_reader, 
      stream_writer< type_writer< StreamableType >, Delimiter >, 
      MaxSize, 
      Derived > {
    };

    struct type 
      : public basic_file< istream_object_buffer_alias, TimePolicy, PermissionPolicy >{
      type( StreamableType& so ) {
	type_writer< StreamableType > w(so);
	stream_writer< type_writer< StreamableType >, Delimiter > ww(w);
	this->init_writer(ww);
      }      
    }; 
  };

  template< class StreamableType > 
  typename istream_object_file< StreamableType >::type*
  make_istream_object_file( StreamableType& so ){
    return new typename istream_object_file< StreamableType >::type(so);
  }

  template< 
    class StreamableType,
    char Delimiter = '\n',
    int MaxSize = 4096,
    template <class> class TimePolicy = default_time,
    template <class> class PermissionPolicy = default_file_permissions
    >
  struct iostream_object_file{
    template<
      class Derived
      >
    struct iostream_object_buffer_alias 
      : public generic_buffer< 
      stream_reader< type_reader< StreamableType >, Delimiter >, 
      stream_writer< type_writer< StreamableType >, Delimiter >, 
      MaxSize, 
      Derived > {
    };

    struct type 
      : public basic_file< iostream_object_buffer_alias, TimePolicy, PermissionPolicy >{
      type( StreamableType& so ) {
	type_reader< StreamableType > r(so);
	type_writer< StreamableType > w(so);
	stream_reader< type_reader< StreamableType >, Delimiter > rr(r);
	stream_writer< type_writer< StreamableType >, Delimiter > ww(w);
       	this->init_reader( rr );
	this->init_writer( ww );
      }      
    }; 
  };

  template< class StreamableType > 
  typename iostream_object_file< StreamableType >::type*
  make_iostream_object_file( StreamableType& so ){
    return new typename iostream_object_file< StreamableType  >::type(so);
  }
}
  
#endif
