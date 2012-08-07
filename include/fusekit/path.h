
#ifndef __FUSEKIT__PATH_H_
#define __FUSEKIT__PATH_H_

#include <list>
#include <string>
#include <sstream>

namespace fusekit{
  struct path : public std::list< std::string >{
    inline
    path( const char* path_str ){
      std::istringstream ps(path_str+1); //skip leading /
      char token[256];
      std::list< std::string > parts;
      while( ps.getline(token,256,'/') ){
	push_back(token);
      }
    }
  };
}

#endif
