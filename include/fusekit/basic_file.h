
#ifndef __FUSEKIT__BASIC_FILE_H
#define __FUSEKIT__BASIC_FILE_H

#include <fusekit/basic_entry.h>
#include <fusekit/file_node.h>
#include <fusekit/default_time.h>
#include <fusekit/default_permissions.h>

namespace fusekit{
  template<
    template <class> class BufferPolicy, 
    template <class> class TimePolicy = default_time,
    template <class> class PermissionPolicy = default_file_permissions
    >
  struct basic_file
    : public basic_entry<
    TimePolicy,
    PermissionPolicy,
    BufferPolicy,
    file_node,
    S_IFREG
    >{
  };
}

#endif


