
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
  // you can hold references to directories (and files) you create
  fusekit::default_directory<>::type& dir_a = daemon.root().add_directory( "a", fusekit::make_default_directory());
  dir_a.add_file("s", fusekit::make_iostream_object_file(s2));

  // or you can using chaining if  you do not need the variable later on
  std::string s3("i am a child of /b");
  daemon.root().add_directory( "b", fusekit::make_default_directory()).
    add_file("s", fusekit::make_iostream_object_file(s3));

  return daemon.run(argc,argv);
}
