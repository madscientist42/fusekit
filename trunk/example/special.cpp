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
#include <fusekit/default_directory.h>
#include <fusekit/stream_object_file.h>
#include <fusekit/new_creator.h>


/// demonstrates how to derive from fusekit::iostream_object_file
///
/// the file simply holds a string as buffer.
/// note that operators << and >> have been overloaded to make this
/// class compatible with fusekit::iostream_object_file. 
struct special_file : public fusekit::iostream_object_file< special_file >::type{
  special_file() 
    : fusekit::iostream_object_file< special_file >::type(*this)
    , buf("hello"){
  }
  std::string buf;
};

std::ostream& operator<<( std::ostream& os, const special_file& f ){
  return os << f.buf;
}

std::istream& operator>>( std::istream& is, special_file& f ){
  return is >> f.buf;
}

/// each newly created special_directory contains three "special_files" called
/// "horst", "klaus" and "dieter".
/// in addition, one may create new special_directory or special_file entries.
/// e.g. via shell:
/// :$ mkdir subdir
/// :$ echo hallo > subdir/newfile
struct special_directory 
  : public fusekit::default_directory<
  /// this enables special_directory to create new special_directory childs
  /// when mkdir is called on/in it.
  fusekit::directory_factory< fusekit::new_creator< special_directory > >,
  /// this enables special_directory to create new special_file childs
  /// when mknod is called on/in it.
  fusekit::file_factory< fusekit::new_creator< special_file > >
  >::type {
  special_directory(){
    this->add_file( "horst", new special_file );
    this->add_file( "klaus", new special_file );
    this->add_file( "dieter", new special_file );
  }
};



/// example program which demonstrates how to create directories
/// which itself may create new directories or files.
int main( int argc, char* argv[] ){
  return fusekit::daemon< special_directory >::instance().run(argc,argv);
}
