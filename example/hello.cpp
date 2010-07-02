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

///  if fusekit headers have been installed and fuse package 
/// has been installed, compile and link like this:
/// g++ hello.cpp `pkg-config --cflags --libs fuse` \
/// -DFUSE_USE_VERSION=27 -o hellofs

#include <fusekit/daemon.h>
#include <fusekit/stream_callback_file.h>

/// free function which will be called
/// when the virtual file "hello.txt" is read
int hello( std::ostream& os ){
  os << "hello world!";
  return 0;
}

/// example which demonstrates how to expose
/// data through a free function callback.
/// after program has been started (see below)
/// you can find a single file called hello.txt within
/// the mountpoint/mount-directory. try to read it
/// with cat( e.g. cat hello_mnt/hello.txt).
/// 
/// start from shell like this:
/// $ mkdir hello_mnt
/// $ hellofs hello_mnt
int main( int argc, char* argv[] ){
  fusekit::daemon<>& daemon = fusekit::daemon<>::instance();
  daemon.root().add_file(
			 "hello.txt", 
			 /// create an ostream_callback_file instance
			 /// with auto deduced template parameters
			 fusekit::make_ostream_callback_file(hello)
			 );
  /// runs the daemon at the mountpoint specified in argv
  /// and with other options if specified
  return daemon.run(argc,argv);
}
