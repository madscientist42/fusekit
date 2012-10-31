
/// manually building example
/// ----------------------------------------------------
///  if fusekit headers have been installed and fuse package 
/// is available, compile and link like this:
/// g++ hello_tr1.cpp `pkg-config --cflags --libs fuse` \
/// -DFUSE_USE_VERSION=27 -o hellotr1fs

#include <string>
#include <iostream>
#include <tr1/functional>
#include <fusekit/daemon.h>
#include <fusekit/stream_function_file.h>


/// free / global function which will be called
/// when the virtual file "hello.txt" is read
int streamout_string(  std::ostream& os, std::string& s ){
  os << s;
  return 0;
}

/// example program which demonstrates how to expose
/// or receive data through a free function callback.
/// after starting/mounting one should see a single file
/// called hello_tr1.txt under the mountpoint. try to read it
/// with cat( e.g. cat hello_mnt/hello_tr1.txt).
/// 
/// start from shell like this:
/// $ mkdir hello_mnt
/// $ hellofs hello_mnt 
int main( int argc, char* argv[] ){
  fusekit::daemon<>& daemon = fusekit::daemon<>::instance();
  std::string greeting("hello world!");
  using namespace std::tr1::placeholders;
  daemon.root().add_file(
  			 "hello_tr1.txt", 
			 /// create an ostream_callback_file instance
			 /// with auto deduced template parameters
			 fusekit::make_ostream_function_file( std::tr1::bind( streamout_string, _1, greeting ))
			 );
  /// runs the daemon at the mountpoint specified in argv
  /// and with other options if specified
  return daemon.run(argc,argv);
}
