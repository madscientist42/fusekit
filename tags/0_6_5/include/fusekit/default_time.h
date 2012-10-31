
#ifndef __FUSEKIT__DEFAULT_TIME_H
#define __FUSEKIT__DEFAULT_TIME_H

#include <time.h>
#include <fusekit/time_fields.h>

namespace fusekit{

  template<
    class Derived
    >
  struct default_time {

    default_time() : 
      _change_time( ::time(NULL) ),
      _modification_time( _change_time ),
      _access_time( _change_time ) {
    }
	 
    time_t modification_time() {
      return _modification_time;
    }

    time_t change_time() {
      return _change_time;
    }

    time_t access_time() {
      return _access_time;
    }

    void update( int mask ){
      const time_t now(::time(NULL));
      if( mask & fusekit::change_time ) {
	_change_time = now;
      }
      if( mask & fusekit::modification_time ) {
	_modification_time = now;
      }
      if( mask & fusekit::access_time ) {
	_access_time = now;
      }
    }

  private:
    time_t _change_time;
    time_t _modification_time;
    time_t _access_time;
  };
}

#endif


