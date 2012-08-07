
#ifndef __FUSEKIT__NO_STREAM_READER_H
#define __FUSEKIT__NO_STREAM_READER_H

#include <error.h>
#include <fusekit/entry.h>

namespace fusekit{
  struct no_stream_reader {
    int operator()( char*, size_t, off_t){
      return -EIO;
    }
  };

}

#endif
