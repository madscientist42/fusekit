# requirements #

The c++ extension std::tr1::unordered\_map is required. fusekit has been tested with the following compilers are:
  * g++ 4.2.4
  * g++ 3.4.4
If your stl implementation does not offer <tr1/unorderd\_map>, the [boost::tr1](http://www.boost.org/doc/libs/1_43_0/doc/html/boost_tr1.html) replacement maybe used instead

# runtime state #

Many daemons read in a configuration file at startup and then never change parameters again until the next program restart. Others support a reload mechanism, which does not quit the provided services between parameter changes. Assuming nobody has changed the configuration file after starting the daemon, one may read back all the parameter by looking at the configuration file. Anyhow, if the daemon's state changes on behalf of an external event, this is not reflected in the config file…. Daemons or other processes with some kind of lifetime or life-cycle often require to expose their variables (state) at runtime. Either to observe or to modify its behavior one needs access to them.

# benefits of being a file #

Everything is a file! Thanks to this unix mantra, there are many big and small tools available for working on / with file. Most are simple yet powerful and proven command line tools, in utmost cases available from an ordinary shell. To list a few:

  * **cd** and **ls** let you explore a filesystem
  * **cat** and **echo** let you read and write to it
  * **tar** helps you backup and restore your filesystem's state
  * **nfs** or other techniques even make your filesystem remotely accessible
  * **find** and **grep** will dig through your filesystem
  * **language bindings** are gratuitous, since fileoperations are available in almost any programming or scripting language
  * **chown** and **chmod** provide fine grained access control using unix groups amd users
etc.

just the triplet of cd, ls and cat can offer you a level of **introspection**, that may save you lifetimes of debugging. all you need is a shell (via serial, telnet, ssh)!

# performance #

Speaking in numbers: 0.1ms-1.0ms + X per file access, where X is the stuff you are doing inside the callbacks. The first part of the time is **mainly depending on your RAM bandwidth and cache size** and in general **does not benefit from MHZ**. Note that at least four context switches occur when your filesystem “communicates” with another process through any file operation like read or write.

The performance strongly depends on the size and depth of your filesystem's hierarchy and your usage profile. Nothing is for free and for fusekit **memory and context switches are the costs**. On desktop systems this should never be a problem, on smaller (embedded) systems with limited resources (>32mb ram, >100mhz) a magnitude of thousands of file objects and a depth of about seven is an empiric upper limit. There are many ways to reduce the memory costs, like serving the fileobjects on demand for instance.