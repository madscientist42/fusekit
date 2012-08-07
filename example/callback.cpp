
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
