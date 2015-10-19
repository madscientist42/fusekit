# About #
fusekit is an object oriented c++ binding of [FUSE](http://fuse.sourceforge.net) . While [FUSE](http://fuse.sourceforge.net) provides a great c api / library which enables you to implement full-featured filesystems in userspace, it still requires some work to get things up and running. On top of [FUSE](http://fuse.sourceforge.net), fusekit has been designed to ease this task. In opposite to the [FUSE](http://fuse.sourceforge.net) api, fusekit's api reflects a filesystem's hierarchical nature as it provides concepts of directories and files. fusekit is **header-only** and highly customizable through the usage of **template techniques**.

Despite helping you implement traditional filesystem, which represent data, fusekit's strength is to **expose runtime state** of daemons, userspace drivers or other processes with a reasonable lifetime. Following this approach one may end up embedding objects into a (virtual) filesystem hierarchy, where directories model object instances and files its attributes, comparable to sysfs or configfs. In this context, fusekit (and FUSE) may be considered some kind of interprocess communication mechanism (ipc) through means of fileoperations, which comes with a huge swiss-army knife for introspection, remote-access, backup and other tasks.

fusekit has been used successfully on an embedded powerpc platform within **production environment**.

# Examples #
All examples can be either found [here](http://code.google.com/p/fusekit/source/browse/#svn/trunk/example) or within the tarball under the downloads section.

## Hello World! ##

```
#include <fusekit/daemon.h>
#include <fusekit/stream_callback_file.h>
 
int hello( std::ostream& os ){
  os << "hello world!" << std::endl;
  return 0;
}
 
int main( int argc, char* argv[] ){
  fusekit::daemon<>& daemon = fusekit::daemon<>::instance();
  daemon.root().add_file(
                         "hello.txt", 
                         fusekit::make_ostream_callback_file(hello)
                         );
  return daemon.run(argc,argv);
}
```

This example demonstrates how to expose data through a free function callback ( `int hello( std::ostream& os )`). After the program has been started, you can find a single file called hello.txt within the mountpoint/mount-directory specified in the cmdline. Try to read it with cat( e.g. cat hello\_mnt/hello.txt). Everytime you read the file hello.txt, the function `int hello( std::ostream& os )` will be called.
Start the filesystem from shell like this:
```
$mkdir hello_mnt
$hellofs hello_mnt
$cat hello_mnt/hello.txt
```