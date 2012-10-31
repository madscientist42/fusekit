
#ifndef __FUSEKIT__DEFAULT_DIRECTORY_H
#define __FUSEKIT__DEFAULT_DIRECTORY_H

#include <fusekit/basic_directory.h>
#include <fusekit/directory_node.h>
#include <fusekit/directory_factory.h>
#include <fusekit/file_factory.h>


namespace fusekit{

  template<
    class DirectoryFactory = directory_factory<>,
    class FileFactory = file_factory<>
    >
  struct default_directory {
    template<
      class Derived
      >
    struct directory_node_alias : 
      public directory_node< 
      DirectoryFactory,
      FileFactory,
      Derived
      >{
    };
    typedef basic_directory< directory_node_alias > type;
  };

  inline
  default_directory<>::type* make_default_directory(){
    return new default_directory<>::type;
  }
  
}

#endif


