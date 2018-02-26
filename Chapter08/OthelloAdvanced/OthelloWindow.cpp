#include "OthelloWidget.h"
#include "OthelloWindow.h"
#include <QtWidgets>

OthelloWindow::OthelloWindow(QWidget *parentWidget /*= nullptr*/)
 :MainWindow(parentWidget) {
  setWindowTitle(tr("Othello Advanced"));
  resize(1000, 500);

  m_othelloWidgetPtr = new OthelloWidget(this);
  setCentralWidget(m_othelloWidgetPtr);

  { QMenu* gameMenuPtr = menuBar()->addMenu(tr("&Game"));
    connect(gameMenuPtr, SIGNAL(aboutToShow()),
            this, SLOT(onMenuShow()));

    { QMenu* computerStartsMenuPtr =
        gameMenuPtr->addMenu(tr("&Computer Starts"));
      connect(computerStartsMenuPtr, SIGNAL(aboutToShow()),
              this, SLOT(onMenuShow()));

      addAction(computerStartsMenuPtr, tr("Computer &Black"),
                SLOT(onComputerStartsBlack()), 0,
                tr("Computer Black"), nullptr,
                tr("Computer Black"),
                LISTENER(isComputerStartsBlackEnabled));

      addAction(computerStartsMenuPtr, tr("Computer &White"),
                SLOT(onComputerStartsWhite()), 0,
                tr("Computer White"), nullptr,
                tr("Computer White"),
                LISTENER(isComputerStartsWhiteEnabled));
    }

    { QMenu* humanStartsMenuPtr =
        gameMenuPtr->addMenu(tr("&Human Starts"));
      connect(humanStartsMenuPtr, SIGNAL(aboutToShow()),
              this, SLOT(onMenuShow()));

      addAction(humanStartsMenuPtr, tr("Human &Black"),
                SLOT(onHumanStartsBlack()), 0, tr("Human Black"),
                nullptr, tr("Human Black"),
                LISTENER(isHumanStartsBlackEnabled));

      addAction(humanStartsMenuPtr, tr("Human &White"),
                SLOT(onHumanStartsWhite()), 0, tr("Human White"),
                nullptr, tr("Human White"),
                LISTENER(isHumanStartsWhiteEnabled));
    }

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

OthelloWindow::~OthelloWindow() {
  delete m_othelloWidgetPtr;
}
