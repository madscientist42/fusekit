
#ifndef __FUSEKIT__NO_STREAM_WRITER_H
#define __FUSEKIT__NO_STREAM_WRITER_H

#include <error.h>
#include <fusekit/entry.h>

namespace fusekit{
  struct no_stream_writer {
    int operator()( const char*, size_t, off_t){
      return -EROFS;
    }
  };

}

#endif
