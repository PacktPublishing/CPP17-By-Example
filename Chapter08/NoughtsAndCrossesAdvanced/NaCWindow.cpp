#include "NaCWindow.h"
#include <QtWidgets>

NaCWindow::NaCWindow(QWidget *parentWidget /*= nullptr*/)
 :MainWindow(parentWidget) {
  setWindowTitle(tr("Noughts and Crosses Advanced"));
  resize(1000, 500);

  m_nacWidgetPtr = new NaCWidget(this);
  setCentralWidget(m_nacWidgetPtr);

  { QMenu* gameMenuPtr = menuBar()->addMenu(tr("&Game"));
    connect(gameMenuPtr, SIGNAL(aboutToShow()),
            this, SLOT(onMenuShow()));

    { QMenu* computerStartsMenuPtr =
        gameMenuPtr->addMenu(tr("&Computer Starts"));
      connect(computerStartsMenuPtr, SIGNAL(aboutToShow()),
              this, SLOT(onMenuShow()));

      addAction(computerStartsMenuPtr, tr("Computer &Nought"),
                SLOT(onComputerStartsNought()), 0,
                tr("Computer Nought"), nullptr,
                tr("Computer Nought"),
                LISTENER(isComputerStartsNoughtEnabled));

        addAction(computerStartsMenuPtr, tr("Computer &Cross"),
                  SLOT(onComputerStartsCross()), 0,
                  tr("Computer Cross"), nullptr,
                  tr("Computer Cross"),
                  LISTENER(isComputerStartsCrossEnabled));
    }

    { QMenu* humanStartsMenuPtr =
        gameMenuPtr->addMenu(tr("&Human Starts"));
      connect(humanStartsMenuPtr, SIGNAL(aboutToShow()),
              this, SLOT(onMenuShow()));

      addAction(humanStartsMenuPtr, tr("Human &Nought"),
                SLOT(onHumanStartsNought()), 0, tr("Human Nought"),
                nullptr, tr("Human Nought"),
                LISTENER(isHumanStartsNoughtEnabled));

      addAction(humanStartsMenuPtr, tr("Human &Cross"),
                SLOT(onHumanStartsCross()), 0, tr("Human Cross"),
                nullptr, tr("Human Cross"),
                LISTENER(isHumanStartsCrossEnabled));
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

NaCWindow::~NaCWindow() {
  delete m_nacWidgetPtr;
}
