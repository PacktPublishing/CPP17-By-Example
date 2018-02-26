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

bool OthelloWidget::isBlackStartsEnabled() {
  return !isGameInProgress();
}

void OthelloWidget::onBlackStarts() {
  setGameInProgress(true);
  m_nextMark = Black;
  update();
}

bool OthelloWidget::isWhiteStartsEnabled() {
  return !isGameInProgress();
}

void OthelloWidget::onWhiteStarts() {
  setGameInProgress(true);
  m_nextMark = White;
  update();
}

void OthelloWidget::mouseMark(int row, int column) {
  set(row, column, m_nextMark);
  turn(row, column, m_nextMark);
  update();
  checkWinner();
  m_nextMark = (m_nextMark == Black) ? White : Black;
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

void OthelloWidget::checkWinner() {
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

    if (blacks == whites) {
      text.sprintf("A Draw.");
    }
    else if (blacks > whites) {
      text.sprintf("The Winner: Black");
    }
    else {
      text.sprintf("The Winner: White");
    }

    messageBox.setText(text);
    messageBox.setStandardButtons(QMessageBox::Ok);
    messageBox.exec();
    setGameInProgress(false);

    clearGrid();
    update();
  }
}

void OthelloWidget::turn(int row, int column, Mark mark) {
  QSet<QPair<int,int>> turnSet;
  calculateMark(row, column, mark, turnSet);

  for (QPair<int,int> pair : turnSet) {
    int row = pair.first, column = pair.second;
    set(row, column, mark);
  }
}

void OthelloWidget::calculateMark(int row, int column,
                 Mark playerMark, QSet<QPair<int,int>>& totalSet){
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

  for (int index = 0; index < arraySize; ++index) {
    QPair<int,int> pair = directionArray[index];
    int rowStep = pair.first, columnStep = pair.second,
        currRow = row, currColumn = column;
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
