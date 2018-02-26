#include "OthelloWidget.h"
#include "OthelloWindow.h"

#include <QTime>
#include <CTime>
#include <CAssert>
using namespace std;

OthelloWidget::OthelloWidget(QWidget* parentWidget)
 :GameWidget(ROWS, COLUMNS, parentWidget) {
  // Empty.
}

bool OthelloWidget::isComputerStartsBlackEnabled() {
  return !isGameInProgress();
}

bool OthelloWidget::isComputerStartsWhiteEnabled() {
  return !isGameInProgress();
}

bool OthelloWidget::isHumanStartsBlackEnabled() {
  return !isGameInProgress();
}

bool OthelloWidget::isHumanStartsWhiteEnabled() {
  return !isGameInProgress();
}

void OthelloWidget::onComputerStartsBlack() {
  setGameInProgress(true);
  set(ROWS / 2, COLUMNS / 2, m_computerMark = Black);
  m_humanMark = White;
  update();
}

void OthelloWidget::onComputerStartsWhite() {
  setGameInProgress(true);
  set(ROWS / 2, COLUMNS / 2, m_computerMark = White);
  m_humanMark = Black;
  update();
}

void OthelloWidget::onHumanStartsBlack() {
  setGameInProgress(true);
  m_humanMark = Black;
  m_computerMark = White;
  update();
}

void OthelloWidget::onHumanStartsWhite() {
  setGameInProgress(true);
  m_humanMark = White;
  m_computerMark = Black;
  update();
}

void OthelloWidget::mouseMark(int row, int column) {
  set(row, column, m_humanMark);
  turn(row, column, m_humanMark);
  update();

  if (!checkWinner()) {
/*    QTime stopTime = QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < stopTime) {
      // Empty.
    }*/

    calculateComputerMove();
    update();
    checkWinner();
  }
}

void OthelloWidget::drawMark(QPainter& painter,
                             const QRect& markRect, int mark) {
  painter.setPen(Qt::black);
  painter.drawRect(markRect);
  painter.fillRect(markRect, Qt::lightGray);

  switch (mark) {
    case Black:
      painter.setPen(Qt::black);
      painter.setBrush(Qt::black);
      painter.drawEllipse(markRect);
      break;

    case White:
      painter.setPen(Qt::white);
      painter.setBrush(Qt::white);
      painter.drawEllipse(markRect);
      break;

    case Empty:
      break;
  }
}

bool OthelloWidget::checkWinner() {
  int blacks = 0, whites = 0, empties = 0;

  for (int row = 0; row < ROWS; ++row) {
    for (int column = 0; column < COLUMNS; ++column) {
      switch (get(row, column)) {
        case Black:
          ++blacks;
          break;

        case White:
          ++whites;
          break;

        case Empty:
          ++empties;
          break;
      }
    }
  }

  if (empties == 0) {
    QMessageBox messageBox(QMessageBox::Information,
                           tr("Victory"), QString());
    QString text;

    if (blacks > whites) {
      text.sprintf("The Winner: %s.", (m_computerMark == Black)
                                      ? "Computer" : "Human");
    }
    else if (whites > blacks) {
      text.sprintf("The Winner: %s.", (m_computerMark == White)
                                      ? "Computer" : "Human");
    }
    else {
      text.sprintf("A Draw.");
    }

    messageBox.setText(text);
    messageBox.setStandardButtons(QMessageBox::Ok);
    messageBox.exec();
    setGameInProgress(false);
    clearGrid();
    update();

    return true;
  }

  return false;
}

void OthelloWidget::calculateComputerMove() {
  int maxTurnSetSize = 0, maxNeighbours = 0;
  QList<QSet<QPair<int,int>>> maxTurnSetList;
  QList<QPair<int,int>> maxNeighboursList;

  for (int row = 0; row < ROWS; ++row) {
    for (int column = 0; column < COLUMNS; ++column) {
      if (get(row, column) == Empty) {
        QSet<QPair<int,int>> turnSet;
        int neighbours = 0;
        calculateTurns(row, column, m_computerMark,
                       turnSet, neighbours);
        int turnSetSize = turnSet.size();

        if (turnSetSize > maxTurnSetSize) {
          maxTurnSetSize = turnSetSize;
          turnSet.insert(QPair<int,int>(row, column));
          maxTurnSetList.clear();
          maxTurnSetList.append(turnSet);
        }
        else if ((turnSetSize > 0) &&
                 (turnSetSize == maxTurnSetSize)) {
          turnSet.insert(QPair<int,int>(row, column));
          maxTurnSetList.append(turnSet);
        }

        if (neighbours > maxNeighbours) {
          maxNeighbours = neighbours;
          maxNeighboursList.clear();
          maxNeighboursList.append(QPair<int,int>(row, column));
        }
        else if ((neighbours > 0) &&
                 (neighbours == maxNeighbours)) {
          maxNeighboursList.append(QPair<int,int>(row, column));
        }
      }
    }
  }

  if (maxTurnSetSize > 0) {
    srand(time(NULL));
    int index = rand() % maxTurnSetList.size();
    QSet<QPair<int,int>> maxTurnSet = maxTurnSetList[index];

    for (QPair<int,int> position : maxTurnSet) {
      int row = position.first, column = position.second;
      set(row, column, m_computerMark);
    }
  }
  else {
    assert(!maxNeighboursList.empty());
    srand(time(NULL));
    int index = rand() % maxNeighboursList.size();
    QPair<int,int> position = maxNeighboursList[index];
    int row = position.first, column = position.second;
    set(row, column, m_computerMark);
  }
}

void OthelloWidget::turn(int row, int column, Mark mark) {
  QSet<QPair<int,int>> turnSet;
  int neighbours;
  calculateTurns(row, column, mark, turnSet, neighbours);

  for (QPair<int,int> pair : turnSet) {
    int row = pair.first, column = pair.second;
    set(row, column, mark);
  }
}

void OthelloWidget::calculateTurns(int row, int column,
                  Mark playerMark,QSet<QPair<int,int>>& totalSet,
                  int& neighbours) {
  QPair<int,int> directionArray[] =
    {QPair<int,int>(-1, 0),   // North
     QPair<int,int>(-1, 1),   // Northeast
     QPair<int,int>(0, 1),    // East
     QPair<int,int>(1, 1),    // Southeast
     QPair<int,int>(1, 0),    // South
     QPair<int,int>(1, -1),   // Southwest
     QPair<int,int>(0, -1),   // West
     QPair<int,int>(-1, -1)}; // Northwest

  int arraySize =
    (sizeof directionArray) / (sizeof directionArray[0]);

  neighbours = 0;
  int opponentMark = (playerMark == Black) ? White : Black;

  for (int index = 0; index < arraySize; ++index) {
    QPair<int,int> pair = directionArray[index];

    int rowStep = pair.first, columnStep = pair.second,
        currRow = row, currColumn = column;

    if (((row + rowStep) >= 0) && ((row + rowStep) < ROWS) &&
        ((column + rowStep) >= 0) &&
        ((column + columnStep) < COLUMNS) &&
        (get(row + rowStep, column + rowStep) == opponentMark)) {
      ++neighbours;
    }

    QSet<QPair<int,int>> directionSet;

    while (true) {
      currRow += rowStep;
      currColumn += columnStep;

      if ((currRow < 0) || (currRow == ROWS) ||
          (currColumn < 0) || (currColumn == COLUMNS) ||
          (get(currRow, currColumn) == Empty)) {
        break;
      }
      else if (get(currRow, currColumn) == playerMark) {
        totalSet += directionSet;
        break;
      }
      else {
        directionSet.insert(QPair<int,int>(row, column));
      }
    }
  }
}
