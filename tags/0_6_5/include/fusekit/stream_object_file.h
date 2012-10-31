
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
