#include "EditorWindow.h"
#include <QtWidgets>

EditorWindow::EditorWindow(QWidget *parentWidgetPtr /*= nullptr*/)
 :MainWindow(parentWidgetPtr) {
  resize(1000, 500);
  m_editorWidgetPtr = new EditorWidget(this);
  setCentralWidget(m_editorWidgetPtr);
  addFileMenu();
}

EditorWindow::~EditorWindow() {
  // Empty.
}

void EditorWindow::keyPressEvent(QKeyEvent* eventPtr) {
  m_editorWidgetPtr->keyPressEvent(eventPtr);
}

void EditorWindow::closeEvent(QCloseEvent* eventPtr) {
  m_editorWidgetPtr->closeEvent(eventPtr);
}
