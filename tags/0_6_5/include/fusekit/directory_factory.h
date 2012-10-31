
#ifndef __FUSEKIT__DIRECTORY_FACTORY_H
#define __FUSEKIT__DIRECTORY_FACTORY_H

#include <string>
#include <tr1/unordered_map>
#include <fusekit/no_lock.h>
#include <fusekit/entry.h>
#include <fusekit/no_creator.h>

namespace fusekit{

  template< class Creator = no_creator, class LockingPolicy = no_lock >
  struct directory_factory : public LockingPolicy {
    typedef std::tr1::unordered_map< std::string, entry* > map_t;
    typedef typename directory_factory< Creator, LockingPolicy >::lock lock;

    ~directory_factory() {
      lock guard(*this);
      map_t::const_iterator e = _added_dirs.begin();
      while( e != _added_dirs.end() ){
	delete e->second;
	++e;
      }
      e = _created_dirs.begin();
      while( e != _created_dirs.end() ){
	delete e->second;
	++e;
      }
    }

    entry* find( const char* name ) {
      lock guard(*this);
      map_t::const_iterator e = _added_dirs.find( name );
      if( e != _added_dirs.end() ) {
  	return e->second;
      }
      e = _created_dirs.find( name );
      if( e != _created_dirs.end() ) {
  	return e->second;
      }
      return 0;
    }

    template< class Child >
    Child& add_directory( const char* name, Child* child ) {
      lock guard(*this);
      const map_t::key_type key( name );
      map_t::iterator e = _added_dirs.find( name );
      if( e != _added_dirs.end() ) {
    	delete e->second;
      }
      _added_dirs[ name ] = child;
      return *child;
    }
    
    int size() {
      lock guard(*this);
      return _added_dirs.size() + _created_dirs.size();
    }

    name_container_t names() {
      lock guard(*this);
      name_container_t names;
      map_t::const_iterator i = _added_dirs.begin();
      while( i != _added_dirs.end() ) {
	names.insert( i->first.c_str() );
	++i;
      }
      i = _created_dirs.begin();
      while( i != _created_dirs.end() ) {
	names.insert( i->first.c_str() );
	++i;
      }
      return names;
    }

    int create( const char* name, mode_t mode ){
      lock guard(*this);
      if( find( name ) ){
	return -EEXIST;
      }
      entry* d = _creator();
      if( !d ){
	return -EROFS;
      }
      int chmod_err = d->chmod( mode );
      if( chmod_err ){
	delete d;
	return chmod_err;
      }
      _created_dirs[name] = d;
      return 0;
    }

    int destroy( const char* name ){
      lock guard(*this);
      entry* ep = 0;
      map_t::const_iterator e = _added_dirs.find( name );
      if( e != _added_dirs.end() ) {
  	ep = e->second;
	_added_dirs.erase(e);
      }
      else if( (e = _created_dirs.find( name )) != _created_dirs.end() ){
	ep = e->second;
	_created_dirs.erase(e);
      }
      
      if( ep ){
	delete ep;
	return 0;
      }
      else{
	return -ENOENT;
      }
    }
  private:
    Creator _creator;
    map_t _added_dirs;
    map_t _created_dirs;
  };

}

#endif


