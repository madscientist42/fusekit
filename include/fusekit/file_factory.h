/*
 * This file is part of fusekit, a c++ convenience wrapper for FUSE.
 *
 * Written by Gerhard Lipp <gerhard_lipp@gmx.de>
 *
 * this library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with fusekit.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __FUX__FILE_FACTORY_H
#define __FUX__FILE_FACTORY_H

#include <string>
#include <tr1/unordered_map>
#include <fusekit/no_lock.h>
#include <fusekit/entry.h>
#include <fusekit/file_node.h>
#include <fusekit/no_creator.h>

namespace fusekit{

  struct no_file_creator{
    entry* operator()(){
      return 0;
    }
  };

  template< class Creator = no_creator, class LockingPolicy = no_lock >
  struct file_factory : public LockingPolicy{
    typedef std::tr1::unordered_map< std::string, entry* > map_t;
    typedef typename file_factory< Creator, LockingPolicy >::lock lock;

    ~file_factory() {
      lock guard(*this);
      map_t::const_iterator e = _added_files.begin();
      while( e != _added_files.end() ){
	delete e->second;
	++e;
      }
      e = _created_files.begin();
      while( e != _created_files.end() ){
	delete e->second;
	++e;
      }
    }

    entry* find( const char* name ) {
      lock guard(*this);
      map_t::const_iterator e = _added_files.find( name );
      if( e != _added_files.end() ) {
  	return e->second;
      }
      e = _created_files.find( name );
      if( e != _created_files.end() ) {
  	return e->second;
      }
      return 0;
    }

    template< class Child >
    Child& add_file( const char* name, Child* child ) {
      lock guard(*this);
      const map_t::key_type key( name );
      map_t::iterator e = _added_files.find( name );
      if( e != _added_files.end() ) {
    	delete e->second;
      }
      _added_files[ name ] = child;
      return *child;
    }
    
    int size() {
      lock guard(*this);
      return _added_files.size() + _created_files.size();
    }

    name_container_t names() {
      lock guard(*this);
      name_container_t names;
      map_t::const_iterator i = _added_files.begin();
      while( i != _added_files.end() ) {
	names.insert( i->first.c_str() );
	++i;
      }
      i = _created_files.begin();
      while( i != _created_files.end() ) {
	names.insert( i->first.c_str() );
	++i;
      }
      return names;
    }

    int create( const char* name, mode_t mode, dev_t type ){
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
      _created_files[name] = d;
      return 0;
    }

    int destroy( const char* name ){
      lock guard(*this);
      entry* ep = 0;
      map_t::const_iterator e = _added_files.find( name );
      if( e != _added_files.end() ) {
  	ep = e->second;
	_added_files.erase(e);
      }
      else if( (e = _created_files.find( name )) != _created_files.end() ){
	ep = e->second;
	_created_files.erase(e);
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
    map_t _added_files;
    map_t _created_files;
  };

}

#endif


