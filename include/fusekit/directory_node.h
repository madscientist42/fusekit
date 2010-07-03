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

#ifndef __FUSEKIT__DIRECTORY_NODE_H
#define __FUSEKIT__DIRECTORY_NODE_H

#include <time.h>
#include <set>
#include <fusekit/entry.h>
#include <fusekit/time_fields.h>

namespace fusekit{

  typedef std::set< const char* > name_container_t;
 
  template<
    class DirectoryFactory,
    class FileFactory,
    class Derived 
    > 
  struct directory_node 
    : public DirectoryFactory
    , public FileFactory {
    
    entry* find( const char* name ) {
      entry* e = directory_factory().find(name);
      if( !e ) {
	e = file_factory().find(name);
      }
      return e;
    }

    int links() {
      return file_factory().size() + directory_factory().size() + 2;
    }

    int readdir( void* buf, fuse_fill_dir_t filler, off_t offset, fuse_file_info& ){
      using namespace std;
      filler( buf, ".", NULL, offset );
      filler( buf, "..", NULL, offset );
      name_container_t names( file_factory().names() );
      name_container_t::const_iterator i = names.begin();
      while( i != names.end() ) {
	filler( buf, *i, NULL, offset );
	++i;
      }
      names = directory_factory().names();
      i = names.begin();
      while( i != names.end() ) {
	filler( buf, *i, NULL, offset );
	++i;
      }
      return 0;
    }

    int mknod( const char* name, mode_t mode, dev_t type){
      const int err = file_factory().create(name,mode,type);
      if( err == 0 ){
	update_change_and_modification_time();
      }
      return err;
    }

    int unlink( const char* name ){
      const int err = file_factory().destroy(name);
      if( err == 0 ){
	update_change_and_modification_time();
      }
      return err;
    }

    int mkdir( const char* name, mode_t mode ){
      const int err = directory_factory().create(name,mode);
      if( err == 0 ){
	update_change_and_modification_time();
      }
      return err;
    }

    int rmdir( const char* name ){
      const int err = directory_factory().destroy(name);
      if( err == 0 ){
	update_change_and_modification_time();
      }
      return err;
    }

  private:
    inline
    DirectoryFactory& directory_factory() {
      return static_cast< DirectoryFactory& >(*this);
    }

    inline
    void update_change_and_modification_time(){
      static_cast< Derived& >(*this).update( fusekit::modification_time | fusekit::change_time );
    }

    inline
    FileFactory& file_factory() {
      return static_cast< FileFactory& >(*this);
    }
  };

}

#endif


