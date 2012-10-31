
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
