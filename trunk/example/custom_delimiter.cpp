
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
