
#include <fusekit/daemon.h>
#include <fusekit/basic_file.h>
#include <fusekit/file_node.h>
#include <fusekit/tracer_buffer.h>
#include <fusekit/default_time.h>
#include <fusekit/default_permissions.h>

using namespace fusekit;

typedef  basic_file< tracer_buffer > tracer_file;

int main( int argc, char* argv[] ){
  fusekit::daemon<>::instance().root().add_file( "trace", new tracer_file );
  return fusekit::daemon<>::instance().run(argc,argv);
}
