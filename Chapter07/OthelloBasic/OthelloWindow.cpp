#include "OthelloWidget.h"
#include "OthelloWindow.h"
#include <QtWidgets>

OthelloWindow::OthelloWindow(QWidget *parentWidget /*= nullptr*/)
 :MainWindow(parentWidget) {
  setWindowTitle(tr("Othello"));
  resize(1000, 500);

  m_othelloWidgetPtr = new OthelloWidget(this);
  setCentralWidget(m_othelloWidgetPtr);

  { QMenu* gameMenuPtr = menuBar()->addMenu(tr("&Game"));
    connect(gameMenuPtr, SIGNAL(aboutToShow()),
            this, SLOT(onMenuShow()));

    addAction(gameMenuPtr, tr("&Black Starts"),
              SLOT(onBlackStarts()), 0,
              tr("Black Starts"), nullptr,tr("Black Starts"),
              LISTENER(isBlackStartsEnabled));

    addAction(gameMenuPtr, tr("&White Starts"),
              SLOT(onWhiteStarts()), 0,
              tr("White Starts"), nullptr, tr("White Starts"),
              LISTENER(isWhiteStartsEnabled));

    gameMenuPtr->addSeparator();

    addAction(gameMenuPtr, tr("&Quit the Game"),
              SLOT(onQuit()),
              QKeySequence(Qt::CTRL + Qt::Key_Q),
              tr("Quit Game"), nullptr, tr("Quit the Game"),
              LISTENER(isQuitEnabled));

    addAction(gameMenuPtr, tr("E&xit"),
              SLOT(onExit()), QKeySequence::Quit);
  }
}

OthelloWindow::~OthelloWindow() {
  delete m_othelloWidgetPtr;
}
