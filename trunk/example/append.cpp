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
 * You should have received a copy of the GNU General Public License
 * along with fusekit.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <fusekit/daemon.h>
#include <fusekit/stream_object_file.h>


/// demonstrates how to derive from fusekit::iostream_object_file
///
/// the file simply holds a string as buffer and is appendable, that
/// is it checks the open mode and only resets content if O_APPEND is not set.
/// note that operators << and >> have been overloaded to make this
/// class compatible with fusekit::iostream_object_file. 
struct append_file : public fusekit::iostream_object_file< append_file >::type{
  append_file() 
    : fusekit::iostream_object_file< append_file >::type(*this)
    , buf("you can add more line with echo blabla >> append"){
  }
  int open(fuse_file_info& fi){
    if( write_flag_set(fi.flags) && (fi.flags & O_APPEND) == 0){
      buf = "";
    }
    return fusekit::iostream_object_file< append_file >::type::open(fi);
  }
  std::string buf;
};

std::ostream& operator<<( std::ostream& os, const append_file& f ){
  return os << f.buf;
}

std::istream& operator>>( std::istream& is, append_file& f ){
  std::string line;
  is >> line;
  if(!f.buf.empty()){
    f.buf += "\n";
  }
  f.buf += line;
  return is;
}

/// example program which demonstrates how to make file 'appendable'.
int main( int argc, char* argv[] ){
  fusekit::daemon<>::instance().root().add_file(
                                                "append",
                                                new append_file);
  return fusekit::daemon<>::instance().run(argc,argv);
}
