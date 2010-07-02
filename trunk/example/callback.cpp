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
#include <fusekit/stream_callback_file.h>

std::string greeting("hello world!");

/// free / global function which will be called
/// when the virtual file "greeting.txt" is read
int read_greeting( std::ostream& os ){
  os << greeting;
  return 0;
}

/// free / global function which will be called
/// when the virtual file "greeting.txt" is written to
int write_greeting( std::istream& is ){
  std::string new_greeting;
  is >> new_greeting;
  if( new_greeting.empty() ){
    return -EIO;
  }
  greeting = new_greeting;
  return 0;
}

/// example program which demonstrates how to expose
/// or receive data through a free function callback.
/// after starting/mounting one should see a single file
/// called greeting.txt under the mountpoint. try to read it
/// with cat( e.g. cat /mnt/callback_mnt/greeting.txt) or write 
/// to it with echo ( e.g. echo horst > /mnt/callback_mnt/greeting.txt)
/// 
/// start from shell like this:
/// $ mkdir greeting_mnt
/// $ callbackfs greeting_mnt 
int main( int argc, char* argv[] ){
  fusekit::daemon<>& daemon = fusekit::daemon<>::instance();
  daemon.root().add_file(
			 "greeting.txt", 
			 /// create an iostream_callback_file instance
			 /// with auto deduced template parameters
			 fusekit::make_iostream_callback_file(read_greeting, write_greeting)
			 );
  /// runs the daemon at the mountpoint specified in some argv
  /// and other options if specified
  return daemon.run(argc,argv);
}
