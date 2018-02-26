#include "EditorWindow.h"
#include <QtWidgets>

EditorWindow::EditorWindow(QWidget *parentWidgetPtr /*= nullptr*/)
 :MainWindow(parentWidgetPtr) {
  resize(1000, 500);

  m_editorWidgetPtr = new EditorWidget(this);
  setCentralWidget(m_editorWidgetPtr);
  addFileMenu();
  addEditMenu();

  { QMenu* formatMenuPtr = menuBar()->addMenu(tr("F&ormat"));
    connect(formatMenuPtr, SIGNAL(aboutToShow()), this,
            SLOT(onMenuShow()));
    addAction(formatMenuPtr, tr("&Font"), SLOT(onFont()),
              0, QString(), nullptr, QString(),
              LISTENER(isFontEnabled));

    { QMenu* alignmentMenuPtr =
             formatMenuPtr->addMenu(tr("&Alignment"));
      connect(alignmentMenuPtr, SIGNAL(aboutToShow()),
              this, SLOT(onMenuShow()));
      QToolBar* alignmentToolBarPtr = addToolBar(tr("Alignment"));
      m_alignmentGroupPtr = new QActionGroup(this);

      addAction(alignmentMenuPtr, tr("&Left"), SLOT(onLeft()),
                QKeySequence(Qt::ALT + Qt::Key_L), tr("left"),
                alignmentToolBarPtr, tr("Left-aligned text"),
                nullptr, LISTENER(isLeftChecked));
      addAction(alignmentMenuPtr, tr("&Center"),
                SLOT(onCenter()),
                QKeySequence(Qt::ALT + Qt::Key_C),
                tr("center"), alignmentToolBarPtr,
                tr("Center-aligned text"), nullptr,
                LISTENER(isCenterChecked));
      addAction(alignmentMenuPtr, tr("&Right"),
                SLOT(onRight()),
                QKeySequence(Qt::ALT + Qt::Key_R),
                tr("right"), alignmentToolBarPtr,
                tr("Right-aligned text"), nullptr,
                LISTENER(isRightChecked));
    }
  }

  m_editorWidgetPtr->setModifiedFlag(false);
}

EditorWindow::~EditorWindow() {
  delete m_alignmentGroupPtr;
}

void EditorWindow::keyPressEvent(QKeyEvent* eventPtr) {
  m_editorWidgetPtr->keyPressEvent(eventPtr);
}

void EditorWindow::closeEvent(QCloseEvent* eventPtr) {
  m_editorWidgetPtr->closeEvent(eventPtr);
}
