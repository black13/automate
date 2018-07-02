
RESOURCES     = automatehandler.qrc

QT += widgets printsupport
FORMS = ./src/ui/AutomateHandlerWidget.ui \
./src/ui/GraphicsViewMainWindow.ui \
./src/ui/treeViewMainWindow.ui

HEADERS       = ./src/AbstractView.h \
./src/automate.h \
./src/automatehandler.h \
./src/backend/AbstractTreeItem.h \
./src/backend/AutomateRoot.h \
./src/backend/meta_automate.h \
./src/backend/meta_node.h \
./src/backend/node.h \
./src/backend/node_alphabet.h \
./src/backend/node_connection.h \
./src/backend/objectCounter.h \
./src/backend/objectProperty.h \
./src/backend/SymbolTable.h \
./src/GraphicsView/GraphicsItemModelExtension.h \
./src/GraphicsView/GraphicsScene.h \
./src/GraphicsView/graphicsView.h \
./src/GraphicsView/ItemView.h \
./src/GraphicsView/SceneItem_Connection.h \
./src/GraphicsView/SceneItem_ConnectionHandle.h \
./src/GraphicsView/SceneItem_LabelEditor.h \
./src/GraphicsView/SceneItem_Node.h \
./src/GraphicsView/SceneItem_Types.h \
./src/Model.h \
./src/TreeView/treeView.h \
./src/unused/automate_algorithms.h \
./src/unused/orderedpair.h \
./src/viewHandler.h

SOURCES       = ./src/AbstractView.cpp \
./src/automate.cpp \
./src/automatehandler.cpp \
./src/backend/AbstractTreeItem.cpp \
./src/backend/AutomateRoot.cpp \
./src/backend/meta_node.cpp \
./src/backend/node.cpp \
./src/backend/node_connection.cpp \
./src/backend/objectCounter.cpp \
./src/backend/objectProperty.cpp \
./src/backend/SymbolTable.cpp \
./src/GraphicsView/GraphicsItemModelExtension.cpp \
./src/GraphicsView/GraphicsScene.cpp \
./src/GraphicsView/graphicsView.cpp \
./src/GraphicsView/ItemView.cpp \
./src/GraphicsView/SceneItem_Connection.cpp \
./src/GraphicsView/SceneItem_ConnectionHandle.cpp \
./src/GraphicsView/SceneItem_LabelEditor.cpp \
./src/GraphicsView/SceneItem_Node.cpp \
./src/main.cpp \
./src/Model.cpp \
./src/TreeView/treeView.cpp \
./src/unused/automate_algorithms.cpp \
./src/viewHandler.cpp 


unix:!mac:!vxworks:!integrity:!haiku:LIBS += -lm

# install
target.path = .
INSTALLS += target
