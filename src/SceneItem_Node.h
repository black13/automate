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
/**
 @author Joachim Schiele <js@lastlog.de>
 */

#ifndef SCENEITEM_NODE_H
#define SCENEITEM_NODE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QPainterPath>
#include <QPersistentModelIndex>
#include <QGraphicsView>
#include <QMenu>
#include <QGraphicsSceneMouseEvent>
#include <QMultiMap>

#include "GraphicsScene.h"
#include "SceneItem_Connection.h"
#include "SceneItem_Types.h"
#include "SceneItem_LabelEditor.h"

#define NODERADIUS 24

class SceneItem_Connection;
class SceneItem_LabelEditor;

/*! represents a node in the QGraphicsScene which can have childs. Childs are incomming and outgoing
** connections as both need to be repainted when either the startNode or endNode is moved.*/
class SceneItem_Node : public QGraphicsItem {
  friend class SceneItem_Connection;
  public:
    /*! the QPersistentModelIndex must be valid troughout the lifetime of the SceneItem_Node */
    SceneItem_Node( QPersistentModelIndex index );
    /*! either called by reset() in the ItemView or when an object is really deleted in data */
    ~SceneItem_Node();
    /*! used to identify a object by a class of objects, see it's implementation */
    int type() const;
    /*! this member function tracks the following changes:
     **  - itemlabel changes
     **  and is indirectly called by dataChanged() from the Model and
     **  directly called by our GraphicsScene dataChanged handler*/
    void updateData();
    /*! called when a new connection is added or deleted
    ** - the algorithm creates groups of connections with the same destination
    **  - NULL desination is not handled
    **  - loop desitnation is in one group
    **  - connections to the same destinations are grouped */
    void layoutChange();
    /*! This index is needed to map QModelIndexes to QGraphicsItems. Since we need to
    ** store the QModelIndexe we are enforced to use a QPersistentModelIndex which
    ** implicitly updates if the date in the model changes. That means when you remove
    ** the connection 3 (out of 7 connections) all QPersistentModelIndex (4,5,6,7) are
    ** automatically updated to the new pos: 3,4,5,6 which is very important! */
    QPersistentModelIndex index;
  private:
    /*! used for labelItem editing */
    void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event );
    /*! see the Qt docs about QGraphicsItem */
    QPainterPath shape() const;
    /*! used to track item highlighting */
    void hoverEnterEvent( QGraphicsSceneHoverEvent * event );
    /*! used to track item highlighting */
    void hoverLeaveEvent( QGraphicsSceneHoverEvent * event );
    /*! currently not used but function stub might be helpful */
    void contextMenuEvent( QGraphicsSceneContextMenuEvent * event );
    /*! this is a quite static rect 'in' which the item is drawn. one might extend it's functionality
    ** to reflect long label names. right now long labels only get redrawn when the text is in the
    ** boudingbox or when 'u' is used to update the whole scene drawing */
    QRectF boundingRect() const;
    /*! container which holds all incomming and outgoing connections. This childs are incomming and
    ** outgoing connections as both need to be repainted when either the startNode or endNode is moved.*/
    QList<SceneItem_Connection *> ConnectionItems;
    /*! represents the id of a node, it is initialized and updated through updateData() */
    QString m_label;
    /*! a copy of the node label property, it is initialized and updated through updateData() */
    QString m_label_custom;
    /*! a copy of the node start property, it is initialized and updated through updateData() */
    bool start;
    /*! a copy of the node final property, it is initialized and updated through updateData() */
    bool final;
    /*! this state enabled an object hoovering indication which improves use and feel */
    bool hovering;
    /*! ... */
    qreal penWidth;
    /*! labelEditor is used for inline label editing on doubleClick on this node */
    SceneItem_LabelEditor* labelEditor;
  protected:
    /*! adds a SceneItem_Connection* to the child items list*/
    void addConnection( SceneItem_Connection* ci );
    /*! removes a SceneItem_Connection* to the child items list*/
    bool removeConnection( SceneItem_Connection* ci );
    /*! update connections when a node is moved so that it is drawing to the right 'changed' position */
    QVariant itemChange( GraphicsItemChange change, const QVariant &value );
    /*! see the Qt docs about QGraphicsItem */
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
};

#endif
