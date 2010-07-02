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

#include <sstream>
#include <algorithm>
#include <iterator>
#include <fusekit/daemon.h>
#include <fusekit/stream_callback_file.h>

std::string sentence("i contain newlines\nohoho");

int read_sentence( std::ostream& os ){
  using namespace std;
  copy( sentence.begin(),
	sentence.end(),
	ostreambuf_iterator< char >(os)
	);
  return 0;
}

int write_sentence( std::istream& is ){
  using namespace std;
  sentence.clear();
  copy( istreambuf_iterator< char >(is),
	istreambuf_iterator< char >(),
	back_inserter(sentence)
	);
  return 0;
}

typedef fusekit::iostream_callback_file< 
  int (*)(std::ostream&),
  int (*)(std::istream&), 
  4096, 
  '.' 
  >::type custom_delimiter_file_t;

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
			 "sentence.txt", 
			 /// create an ostream_callback_file instance
			 /// with auto deduced template parameters
			 new custom_delimiter_file_t(read_sentence,write_sentence)
			 );
  /// runs the daemon at the mountpoint specified in argv
  /// and with other options if specified
  return daemon.run(argc,argv);
}
