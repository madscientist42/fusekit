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


struct sfi_tuple {
  int i;
  float f;
  std::string s;
};

std::ostream& operator<<( std::ostream& os, const sfi_tuple& t ){
  os << t.s 
     << " " 
     << t.i 
     << " " 
     << t.f;
  return os;
}

std::istream& operator>>( std::istream& is, sfi_tuple& t ){
  is >> t.s 
     >> t.i 
     >> t.f;
  return is;
}


/// example program which demonstrates how to expose streamable objects.
/// iostream_object_file requires the respective type to have
/// operator<< available. all built-in types meet this requirement.
///
/// after starting/mounting one should see some files directly under.
/// the specified mountpoint.
/// start this process like this:
/// stream_object /mnt/callback_mnt
int main( int argc, char* argv[] ){

  fusekit::daemon<>& daemon = fusekit::daemon<>::instance();

  std::string s( "i am a writeable string");
  daemon.root().add_file("string", fusekit::make_iostream_object_file(s));

  int i = 3;
  daemon.root().add_file("int", fusekit::make_iostream_object_file(i));

  float f = 4.2;
  daemon.root().add_file("float", fusekit::make_iostream_object_file(f));

  std::string sp( "sorry, i am a not writeable string");
  daemon.root().add_file("readonly_string", fusekit::make_ostream_object_file(sp));

  sfi_tuple t;
  t.i = 123;
  t.f = .9876;
  t.s = "sunshine";
  daemon.root().add_file("sfi_tuple", fusekit::make_iostream_object_file(t));

  return daemon.run(argc,argv);
}
