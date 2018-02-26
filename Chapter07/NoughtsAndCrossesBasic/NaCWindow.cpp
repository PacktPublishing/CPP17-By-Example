#include "NaCWindow.h"
#include <QtWidgets>

NaCWindow::NaCWindow(QWidget *parentWidget /*= nullptr*/)
 :MainWindow(parentWidget) {
  setWindowTitle(tr("Noughts and Crosses"));
  resize(1000, 500);

  m_nacWidgetPtr = new NaCWidget(this);
  setCentralWidget(m_nacWidgetPtr);

  { QMenu* gameMenuPtr = menuBar()->addMenu(tr("&Game"));
    connect(gameMenuPtr, SIGNAL(aboutToShow()),
            this, SLOT(onMenuShow()));

    addAction(gameMenuPtr, tr("&Nought Starts"),
              SLOT(onNoughtStarts()), 0,
              tr("Nought Starts"), nullptr, tr("Nought Starts"),
              LISTENER(isNoughtStartsEnabled));

    addAction(gameMenuPtr, tr("&Cross Starts"),
              SLOT(onCrossStarts()), 0,
              tr("Cross Starts"), nullptr, tr("Cross Starts"),
              LISTENER(isCrossStartsEnabled));

    gameMenuPtr->addSeparator();

    addAction(gameMenuPtr, tr("&Quit the Game"),
              SLOT(onQuit()),
              QKeySequence(Qt::CTRL + Qt::Key_Q), tr("Quit Game"),
              nullptr, tr("Quit the Game"),
              LISTENER(isQuitEnabled));

    addAction(gameMenuPtr, tr("E&xit"),
              SLOT(onExit()), QKeySequence::Quit);
  }
}

NaCWindow::~NaCWindow() {
  delete m_nacWidgetPtr;
}
