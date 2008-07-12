// automate implements an automate class in c++ using qt4
// Copyright (C) 2007 Joachim Schiele
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// version 2 as published by the Free Software Foundation
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

#ifndef MODEL_H
#define MODEL_H

#include <QAbstractItemModel>
#include <QVector>
#include <QColor>
#include <QBrush>
#include <QDebug>
#include <QIcon>

#include "AutomateRoot.h"
#include "AbstractTreeItem.h"
#include "node_connection.h"
#include "node.h"

class automate;

namespace customRole {
enum CustomRole {
  IdRole = Qt::UserRole,
  FinalRole,
  StartRole,
  SymbolIndexRole,
  CustomLabelRole,
  SortRole
};
}

class Model : public QAbstractItemModel {
  // FIXME only make the special function reset() and layoutChanged() a
  //       friend not whe whole class
  friend class automate;//::reset();
  public:
    Model( AbstractTreeItem* root, QObject* parent = 0 );
    QModelIndex index( int row, int column, const QModelIndex & parent ) const;
    QModelIndex parent( const QModelIndex & index ) const;
    int rowCount( const QModelIndex & parent ) const;
    int columnCount( const QModelIndex & parent ) const;
    QVariant data( const QModelIndex &, int role ) const;
    bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

    bool removeItems( QList<QPersistentModelIndex> itemList );
    bool insertNode();
    bool insertConnection( QModelIndex startItem, QModelIndex endItem = QModelIndex() );

    unsigned int getSelectedItemType( const QModelIndex& );
    unsigned int getTreeItemType( const QModelIndex& item );
    QModelIndex next_nodeModelIndex( QModelIndex item );

    // symbolTable specific stuff
    int symbol(QString symbol);
    QString symbol(int symbol_index) const;
    int modifySymbol( int position, QString newsymbol);
    int size();

  private:
    QString objectTypeQString( unsigned int input );
    AbstractTreeItem* AbstractTreeItemFromId( unsigned int id );
    bool removeNode( QPersistentModelIndex node );
    bool removeNodes( QList<QPersistentModelIndex> nodeList );
    bool removeConnection( QPersistentModelIndex connection );
    bool removeConnections( QList<QPersistentModelIndex> nodeList );
    QModelIndex getQModelIndexFromAbstractNodeItem( AbstractTreeItem* item );
    AbstractTreeItem* rootItem;
    Qt::ItemFlags flags( const QModelIndex & index ) const;
    bool hasChildren ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    bool insertRows( int row, int count, const QModelIndex & parent = QModelIndex() );
    bool removeRows( int row, int count, const QModelIndex & parent );
};

#endif

