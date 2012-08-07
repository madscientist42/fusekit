
#ifndef __FUSEKIT__STREAM_CALLBACK_FILE_H
#define __FUSEKIT__STREAM_CALLBACK_FILE_H

#include <sstream>
#include <fusekit/basic_file.h>
#include <fusekit/no_stream_reader.h>
#include <fusekit/no_stream_writer.h>
#include <fusekit/stream_reader.h>
#include <fusekit/stream_writer.h>
#include <fusekit/generic_buffer.h>

namespace fusekit {

  template< 
    class ReadCallback, 
    int MaxSize = 4096,
    char Delimiter = '\n',
    template <class> class TimePolicy = default_time,
    template <class> class PermissionPolicy = default_ro_file_permissions
    >
  struct ostream_callback_file{
    template<
      class Derived
      >
    struct ostream_callback_buffer_alias 
      : public generic_buffer< 
      stream_reader< ReadCallback, Delimiter >,
      no_stream_writer,
      MaxSize, 
      Derived > {
    };

    struct type 
      : public basic_file< ostream_callback_buffer_alias, TimePolicy, PermissionPolicy >{
      type( ReadCallback readcb ) {
	stream_reader< ReadCallback, Delimiter > r(readcb);
	this->init_reader(r);
      }      
    }; 
  };

  template< class ReadCallback > 
  typename ostream_callback_file< ReadCallback >::type*
  make_ostream_callback_file( ReadCallback readcb ){
    return new typename ostream_callback_file< ReadCallback >::type(readcb);
  }

  template< 
    class WriteCallback, 
    int MaxSize = 4096,
    char Delimiter = '\n',
    template <class> class TimePolicy = default_time,
    template <class> class PermissionPolicy = default_ro_file_permissions
    >
  struct istream_callback_file{
    template<
      class Derived
      >
    struct istream_callback_buffer_alias 
      : public generic_buffer< 
      no_stream_reader,
      stream_writer< WriteCallback, Delimiter >,
      MaxSize, 
      Derived > {
    };

    struct type 
      : public basic_file< istream_callback_buffer_alias, TimePolicy, PermissionPolicy >{
      type( WriteCallback writecb ) {
	stream_writer< WriteCallback, Delimiter > w(writecb);
	this->init_writer(w);
      }      
    }; 
  };

  template< class WriteCallback > 
  typename istream_callback_file< WriteCallback >::type*
  make_istream_callback_file( WriteCallback writecb ){
    return new typename istream_callback_file< WriteCallback >::type(writecb);
  }

  template< 
    class ReadCallback, 
    class WriteCallback, 
    int MaxSize = 4096,
    char Delimiter = '\n',
    template <class> class TimePolicy = default_time,
    template <class> class PermissionPolicy = default_file_permissions
    >
  struct iostream_callback_file{
    template<
      class Derived
      >
    struct iostream_callback_buffer_alias 
      : public generic_buffer< 
      stream_reader< ReadCallback, Delimiter >,
      stream_writer< WriteCallback, Delimiter >,
      MaxSize, 
      Derived > {
    };

    struct type 
      : public basic_file< iostream_callback_buffer_alias, TimePolicy, PermissionPolicy >{
      type( ReadCallback readcb, WriteCallback writecb ) {
	stream_writer< WriteCallback, Delimiter > w(writecb);
	stream_reader< ReadCallback, Delimiter > r(readcb);
	this->init_reader(r);
	this->init_writer(w);
      }      
    }; 
  };

  template< class ReadCallback, class WriteCallback > 
  typename iostream_callback_file< ReadCallback, WriteCallback >::type*
  make_iostream_callback_file( ReadCallback readcb, WriteCallback writecb ){
    return new typename iostream_callback_file< ReadCallback, WriteCallback >::type(readcb,writecb);
  }
}
  
#endif

