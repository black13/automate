/*
    This file is part of automate.
      Copyright Joachim Schiele
      
    automate is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License.

    automate is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with automate.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
  @author Joachim Schiele <js@lastlog.de>
*/

// Notice: most of this code was taken from the QT4 example code

#include "AbstractTreeItem.h"

AbstractTreeItem::AbstractTreeItem( AbstractTreeItem *parent ) {
//   qDebug() << "AbstractTreeItem Constructor called";
  parentItem = parent;
  ID = 0;
}

AbstractTreeItem::~AbstractTreeItem() {
//   qDebug() <<__FUNCTION__;
}

void AbstractTreeItem::appendChild( AbstractTreeItem *item ) {
  if ( item->parent() != this ) {
    qDebug( "ERROR: you can't add a child to a parent item where \
            the parent of the child doesn't match the parent you want to add it to!" );
  }
  m_childItems.append( item );
}

AbstractTreeItem *AbstractTreeItem::child( int row ) {
  return m_childItems.value( row );
}

int AbstractTreeItem::childCount() const {
  return m_childItems.count();
}


AbstractTreeItem *AbstractTreeItem::parent() {
  return parentItem;
}

int AbstractTreeItem::row() const {
//   qDebug() << (unsigned int) parentItem;
  if ( parentItem )
    return parentItem->m_childItems.indexOf( const_cast<AbstractTreeItem*>( this ) );

  return 0;
}

unsigned int AbstractTreeItem::getId() {
  return ID;
}

QList<AbstractTreeItem*> AbstractTreeItem::childItems() const {
  return m_childItems;
}

void AbstractTreeItem::setParent(AbstractTreeItem *parent) {
  parentItem = parent;
}
