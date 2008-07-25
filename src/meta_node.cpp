// automate implements an automate class in c++ using qt4
// Copyright (C) 2007 Joachim Schiele
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// version 3 as published by the Free Software Foundation
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

/**
  @author Joachim Schiele <js@lastlog.de>
*/


#include "meta_node.h"

void meta_node::addNode ( node* n )
{
  node_container.insert ( n );
}
int meta_node::size()
{
  qDebug("%i", node_container.size());
  return node_container.size();
}

meta_node::meta_node(QList<node*> a){
//     std::cerr << "meta_node(QList<node*> a) CTOR called with QList<node*> argument, ";
//     std::cerr << a.size() << " nodes added" << std::endl;
    for(int i=0; i < a.size(); ++i) {
      node_container.insert(a[i]);
    }
//     std::cerr << "node_container contains: " << size() << " nodes now" << std::endl;
  }

    bool meta_node::operator== ( const meta_node& a )
    {
      if ( a.node_container.size() == this->node_container.size() )
      {
        return ( a.node_container==this->node_container );
      }
      return false;
    }
