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


/// example demonstrates how to create hierarchical structure
/// by creating directories and by by adding files to this
/// newly created directories.
///
/// so directory struture should look like the following
/// (explore with ls and cd from shell)
/// mountpoint/s
/// mountpoint/a/s
/// mountpoint/b/s
/// when started with like
/// $folders mountpoint 
int main( int argc, char* argv[] ){
  fusekit::daemon<>& daemon = fusekit::daemon<>::instance();

  std::string s1("i am a child of /");
  daemon.root().add_file("s", fusekit::make_iostream_object_file(s1));

  std::string s2("i am a child of /a");
  daemon.root().add_directory( "a", fusekit::make_default_directory()).
    add_file("s", fusekit::make_iostream_object_file(s2));

  std::string s3("i am a child of /b");
  daemon.root().add_directory( "b", fusekit::make_default_directory()).
    add_file("s", fusekit::make_iostream_object_file(s3));

  return daemon.run(argc,argv);
}
