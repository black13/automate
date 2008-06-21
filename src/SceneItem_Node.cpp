/****************************************************************************
**
** Copyright (C) 2007-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.0, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** In addition, as a special exception, Trolltech, as the sole copyright
** holder for Qt Designer, grants users of the Qt/Eclipse Integration
** plug-in the right for the Qt/Eclipse Integration to link to
** functionality provided by Qt Designer and its related libraries.
**
** Trolltech reserves all rights not expressly granted herein.
**
** Trolltech ASA (c) 2007
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

//
// C++ Implementation: SceneItem_Node
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "SceneItem_Node.h"

SceneItem_Node::SceneItem_Node( QPersistentModelIndex index ) : QGraphicsItem() {
  setFlags( QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable /*| QGraphicsItem::ItemIsFocusable*/ );
  setAcceptsHoverEvents( true );
//   setData( 0, &index );
//   hovering = false;
  penWidth = 3;

  setZValue( 10 );
  this->index = index;
}

SceneItem_Node::~SceneItem_Node() {
  if ( ConnectionItems.size() != 0 ) {
    qDebug() << "FATAL ERROR: not all nodes have been deleted!!!";
    qDebug() << "inconsistency between the graphicsView and the data (model) might exist";
  }
}

void SceneItem_Node::updateData() {
  if ( scene() == NULL ) {
    qDebug() << "item isn't in any scene, can't query for valid data";
    return;
  }
  int id = (( GraphicsScene* )scene() )->data( index, customRole::IdRole ).toInt();
  QString toolTip = QString( "n%1" ).arg( id );
  setToolTip( toolTip );
  bool start = (( GraphicsScene* )scene() )->data( index, customRole::StartRole ).toBool();
  bool final = (( GraphicsScene* )scene() )->data( index, customRole::FinalRole ).toBool();
  this->label = QString( "%1" ).arg( id );
  this->start = start;
  this->final = final;
  update();
}

QRectF SceneItem_Node::boundingRect() const {
  return QRectF( -NODERADIUS  - penWidth, -NODERADIUS  - penWidth,
                 2*( NODERADIUS  + penWidth ), 2*( NODERADIUS  + penWidth ) );
}

void SceneItem_Node::paint( QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/ ) {
  if ((( GraphicsScene* )scene() )->want_boundingBox() )
    painter->drawRect( boundingRect() );
  if ((( GraphicsScene* )scene() )->want_drawItemShape() )
    painter->drawPath( shape() );

  QBrush brush( Qt::lightGray, Qt::SolidPattern );

  painter->setBrush( brush );
  painter->setPen( Qt::lightGray );
  if ( start ) {
    QRectF rectangle( -NODERADIUS , -NODERADIUS , 2*NODERADIUS , 2*NODERADIUS );
    int startAngle = 120 * 16;
    int spanAngle = 120 * 16;
    painter->drawChord( rectangle, startAngle, spanAngle );
  }

  if ( final ) {
    QRectF rectangle( -NODERADIUS , -NODERADIUS , 2*NODERADIUS , 2*NODERADIUS );
    int startAngle = 300 * 16;
    int spanAngle = 120 * 16;
    painter->drawChord( rectangle, startAngle, spanAngle );
  }

  QPainterPath path;
  path.addEllipse( -NODERADIUS , -NODERADIUS , 2*NODERADIUS , 2*NODERADIUS );
  QPen pen;
  if ( isSelected() ) {
    pen = QPen( Qt::red, penWidth, Qt::DotLine , Qt::RoundCap, Qt::RoundJoin );
    painter->setPen( pen );
    painter->setBrush( QBrush() );
    QPainterPath path1;
    path1.addEllipse( -NODERADIUS - 3, -NODERADIUS - 3, 2*NODERADIUS + 6, 2*NODERADIUS + 6 );
    painter->drawPath( path1 );
  }
  pen = QPen( Qt::black, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );
  painter->setPen( pen );
  painter->setBrush( QBrush() );
  painter->drawPath( path );

// name text
  QString label;
  if ((( GraphicsScene* )scene() )->want_customNodeLabels() ) {
    label = (( GraphicsScene * )scene() )->data( index, customRole::CustomLabelRole ).toString();
    if ( label.size() == 0 )
      label = this->label;
  } else {
    label = this->label;
  }

  QFont f;
  f.setPointSize( 20 );

  QFontMetrics fm( f );
  int width = fm.width( label );
//   int height = fm.height();
  painter->setFont( f );
  painter->drawText( QPointF( -width / 2, 12 ), label );
}

QVariant SceneItem_Node::itemChange( GraphicsItemChange change, const QVariant &value ) {
  if ( /*change == QGraphicsItem::ItemPositionChange ||*/ change == QGraphicsItem::ItemPositionHasChanged ) {
    foreach( SceneItem_Connection  *ci, ConnectionItems ) {
      ci->updatePosition();
    }
  }
  return value;
}

void SceneItem_Node::removeConnection( SceneItem_Connection *ci ) {
//   qDebug() << __FUNCTION__ << (unsigned int)this << " " << (unsigned int)ci ;
  int index = ConnectionItems.indexOf( ci );

  if ( index != -1 )
    ConnectionItems.removeAt( index );
}

// only add new connections if they are not referenced yet
void SceneItem_Node::addConnection( SceneItem_Connection* ci ) {
//   qDebug() << "request to add a connection to this node: " << (unsigned int)this;
  foreach( SceneItem_Connection* c, ConnectionItems ) {
//     qDebug() << "is " << (unsigned int)c << " == " << (unsigned int)ci << " ?";
    if (c == ci) {
//       qDebug() << "item found in node's connection list:, not adding twice";
      return;
    }
  }
//   qDebug() << "item not found in node's connection list: adding a new connection to this node: " << (unsigned int)this;
  ConnectionItems.append( ci );
}

void SceneItem_Node::layoutChange() {
  QVector<SceneItem_Connection *> itemsToAutoLayout;
  foreach( SceneItem_Connection* c, ConnectionItems )
  if ( !c->customTransformation() && !c->isLoop() )
    itemsToAutoLayout.push_back( c );

  qDebug() << "layoutChange(): " << ConnectionItems.size() << "items to layout";

  // we have to build groups of items since we only can handle
  // connections which go to the same destination



  unsigned int size = itemsToAutoLayout.size();
  for(int i=0; i < size; ++i) {
    SceneItem_Connection* c = itemsToAutoLayout[i];
    qreal owner = c->startItem() == this ? 1 : -1;
    qreal factor = (i-(int)(size/2))*owner;
    qDebug() << factor;
    c->setAutoLayoutFactor(factor);
  }
}

QPainterPath SceneItem_Node::shape() const {
  QPainterPath path;
  path.addEllipse( boundingRect() );
  return path;
}

int SceneItem_Node::type() const {
  return SceneItem_NodeType;
}

void SceneItem_Node::hoverEnterEvent( QGraphicsSceneHoverEvent * /*event*/ ) {
//   qDebug() << "hoverEnterEvent";
  if ( !(( GraphicsScene* )scene() )->want_highlight() )
    return;

  foreach( SceneItem_Connection  *ci, ConnectionItems ) {
    ci->highlight( true );
    ci->update();
  }
}

void SceneItem_Node::hoverLeaveEvent( QGraphicsSceneHoverEvent * /*event*/ ) {
//   qDebug() << "hoverLeaveEvent";
  foreach( SceneItem_Connection  *ci, ConnectionItems ) {
    ci->highlight( false );
    ci->update();
  }
}

void SceneItem_Node::contextMenuEvent( QGraphicsSceneContextMenuEvent * /*event*/ ) {
  //FIXME unfinished code!
//   QMenu a;
// //   a.addAction ( "todo del Node", this, SLOT(removeConnections() ) );
// //   a.addSeparator();
//   a.addAction( "-Node-" );
//   a.addAction( "todo start switch" );
//   a.addAction( "todo final switch" );
//   a.addAction( "todo edit label" );
//   a.exec( QCursor::pos() );
}

void SceneItem_Node::mouseDoubleClickEvent( QGraphicsSceneMouseEvent * /*event*/ ) {
  qDebug() << __FUNCTION__;
  qDebug() << "Node: " << (unsigned int)this;
  foreach( SceneItem_Connection* c, ConnectionItems )
    qDebug() << "  \\------- " << (unsigned int)c;

}
