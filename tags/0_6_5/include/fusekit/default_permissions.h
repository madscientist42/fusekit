
#ifndef __FUSEKIT__DEFAULT_PERMISSIONS_H
#define __FUSEKIT__DEFAULT_PERMISSIONS_H

#include <fusekit/entry.h>

namespace fusekit{

  template< 
    mode_t Permissions,
    class Derived
    >
  struct default_permissions {

    default_permissions()
      : _current( Permissions ){
    }

    int access( int permissions ){
      if( permissions & (~_current) )
	return -EACCES;
      return 0;
    }
  
    int chmod( mode_t permissions ){
      static_cast< Derived* >(this)->update(fusekit::modification_time);
      _current = permissions;
      return 0;
    }

    int mode() {
      return _current;
    }

  private:
    int _current;
  };

  template<
    class Derived
    >
  struct default_file_permissions 
    : public default_permissions< 0666, Derived >{
  };

  template<
    class Derived
    >
  struct default_ro_file_permissions 
    : public default_permissions< 0444, Derived >{
  };

  template<
    class Derived
    >
  struct default_wo_file_permissions 
    : public default_permissions< 0222, Derived >{
  };

  template<
    class Derived
    >
  struct default_directory_permissions 
    : public default_permissions< 0755, Derived >{
  };
}

#endif


