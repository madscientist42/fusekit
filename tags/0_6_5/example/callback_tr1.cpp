
#include <iostream>
#include <string>
#include <tr1/functional>
#include <fusekit/daemon.h>
#include <fusekit/stream_function_file.h>


/// a small greeting class to demonstrate 
/// binding to class instances.
struct greeting{
  greeting( const char* g) 
    : _s(g){
  }

  /// read the current greeting buffer.
  int read( std::ostream& os ){
    os << _s;
    return 0;
  }

  /// writes new content to the greeting buffer.
  /// return error if new greeting would be empty.
  int write( std::istream& is ){
    std::string new_greeting;
    is >> new_greeting;
    if( new_greeting.empty() ){
      return -EIO;
    }
    _s = new_greeting;
    return 0;
  }

  /// creates a iostream_function_file (which supports binding)
  /// with class methods bound to it to read and write.
  /// 
  /// greeting's read and write function are used respectively
  /// as callbacks to read from and write to the fusekit::file.
  fusekit::entry* make_fusekit_file(){
    /// blends in bind argument placeholder _1
    using namespace std::tr1::placeholders;
    return fusekit::make_iostream_function_file(
					    std::tr1::bind( &greeting::read, this, _1) , 
					    std::tr1::bind( &greeting::write, this, _1)
					    );
  }
  
private:
  std::string _s;
};



/// example program which demonstrates how to expose
/// or receive data through member function binding.
/// bind is available via tr1 or boost libraries.
/// after starting/mounting one should see two files
/// called tr1_greeting.txt and boost_greeting.txt 
/// within the mountpoint directory. 
/// try to read it with cat(e.g. cat greeting_mnt/tr1_greeting.txt) 
/// or write to it with echo (e.g. echo horst > greeting_mnt/tr1_greeting.txt)
/// 
/// start from shell like this:
/// $ mkdir greeting_mnt
/// $ callbacktr1fs greeting_mnt 
int main( int argc, char* argv[] ){
  fusekit::daemon<>& daemon = fusekit::daemon<>::instance();

  greeting tr1_greeting("hello tr1 users!");
  daemon.root().add_file("tr1_greeting.txt", tr1_greeting.make_fusekit_file());

  greeting boost_greeting("hello boost users!");
  daemon.root().add_file("boost_greeting.txt", boost_greeting.make_fusekit_file());

  return daemon.run(argc,argv);
}
