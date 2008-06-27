//
// C++ Implementation: SceneItem_ConnectionHandle
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "SceneItem_ConnectionHandle.h"
// http://lists.trolltech.com/qt-interest/2007-03/thread00929-0.html

SceneItem_ConnectionHandle::SceneItem_ConnectionHandle() : QGraphicsItem() {
  setFlag( QGraphicsItem::ItemIsMovable );
  move_object_on_mouseMove = false;
}

void SceneItem_ConnectionHandle::setLabel( QString label ) {
  m_label = label;
}

SceneItem_ConnectionHandle::~SceneItem_ConnectionHandle() {
}

QPainterPath SceneItem_ConnectionHandle::shape() const {
  QRectF r( -CIRCLE_FOR_SYNBOL_RADIUS, -CIRCLE_FOR_SYNBOL_RADIUS, 2*CIRCLE_FOR_SYNBOL_RADIUS, 2*CIRCLE_FOR_SYNBOL_RADIUS );
  r.adjusted( -3, -3, 3, 3 );
  QPainterPath path;
  path.addEllipse( r );

  return path;
}


QRectF SceneItem_ConnectionHandle::boundingRect() const {
  QRectF r( -CIRCLE_FOR_SYNBOL_RADIUS, -CIRCLE_FOR_SYNBOL_RADIUS, 2*CIRCLE_FOR_SYNBOL_RADIUS, 2*CIRCLE_FOR_SYNBOL_RADIUS );
  r.adjusted( -3, -3, 3, 3 );
  return r;
}

void SceneItem_ConnectionHandle::paint( QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/ ) {
//   painter->drawPath( shape() );
  QColor c;
  if ( isSelected() )
    c = QColor( "red" );
  else
    c = QColor( "lightgrey" );
  QPen myPen;
  c.setAlphaF( 0.9 );
  myPen.setColor( c );
  painter->setPen( myPen );
  painter->setBrush( c );
  QRectF rectangle( -CIRCLE_FOR_SYNBOL_RADIUS, -CIRCLE_FOR_SYNBOL_RADIUS,
                    2*CIRCLE_FOR_SYNBOL_RADIUS, 2*CIRCLE_FOR_SYNBOL_RADIUS );
//   rectangle.moveTopLeft(diff);
  painter->drawEllipse( rectangle );

  myPen.setColor( QColor( "black" ) );
  painter->setPen( myPen );
//   painter->setBrush( myColor );

//   QString label="34";
  /*  if ((( GraphicsScene* )scene() )->want_customConnectionLabels() ) {
  label = (( GraphicsScene * )scene() )->data( index, customRole::CustomLabelRole ).toString();
  if ( label.size() == 0 )
  label = QString( "%1" ).arg( symbol_index );
  } else {
  label = QString( "%1" ).arg( symbol_index );
  }*/
  QFont f;
  QFontMetrics fm( f );
  int width = fm.width( m_label );
  int height = fm.height();
  painter->drawText( QPointF( -width / 2, height / 4 ), m_label );
}


void SceneItem_ConnectionHandle::mousePressEvent( QGraphicsSceneMouseEvent * event ) {
  move_object_on_mouseMove = true;
//   QGraphicsTextItem::mousePressEvent(event);
}

void SceneItem_ConnectionHandle::mouseMoveEvent( QGraphicsSceneMouseEvent * event ) {
  if ( move_object_on_mouseMove ) {
    moveBy( event->lastPos().x(), event->lastPos().y() );
//     if (parentItem() != NULL)
//       parentItem()->update();
  }
}

void SceneItem_ConnectionHandle::mouseReleaseEvent( QGraphicsSceneMouseEvent * event ) {
  move_object_on_mouseMove = false;
}

void SceneItem_ConnectionHandle::mouseDoubleClickEvent( QGraphicsSceneMouseEvent * event ) {
  qDebug() << __FUNCTION__;
  SceneItem_LabelEditor* f = new SceneItem_LabelEditor(this);
  f->setZValue( 1000.0 );
  f->setTextInteractionFlags( Qt::TextEditorInteraction );
  scene()->addItem( f );
}

QVariant SceneItem_ConnectionHandle::itemChange( GraphicsItemChange change, const QVariant & value ) {
  // only send this event when the labelItem is moved manually
  if ( move_object_on_mouseMove ) {
    if ( parentItem() != NULL )
      (( SceneItem_Connection* )parentItem() )->setCustomTransformation(true);
    if ( scene() && change == ItemPositionChange ) {
      // pos() is the old position, value is the new position.
      if ( parentItem() != NULL ) {
        (( SceneItem_Connection* )parentItem() )->labelItemPositionCallback( pos(), value.toPointF() );
      }
    }
  }
  return QGraphicsItem::itemChange( change, value );
}

void SceneItem_ConnectionHandle::contextMenuEvent( QGraphicsSceneContextMenuEvent * event ) {
  //FIXME add functionality
  QMenu menu;
  QAction *removeConnectionAction = menu.addAction( "FIXME Remove connection" );
  QAction *removeTransformationAction = menu.addAction( "FIXME Remove custom transformation" );
  menu.exec( event->screenPos() );
}


int SceneItem_ConnectionHandle::type() const {
  return SceneItem_ConnectionHandleType;
}
