#include "NaCWidget.h"
#include <CTime>
#include <CAssert>

NaCWidget::NaCWidget(QWidget* parentWidget)
 :GameWidget(ROWS, COLUMNS, parentWidget) {
  // Empty.
}

bool NaCWidget::isComputerStartsNoughtEnabled() {
  return !isGameInProgress();
}

bool NaCWidget::isComputerStartsCrossEnabled() {
  return !isGameInProgress();
}

bool NaCWidget::isHumanStartsNoughtEnabled() {
  return !isGameInProgress();
}

bool NaCWidget::isHumanStartsCrossEnabled() {
  return !isGameInProgress();
}

void NaCWidget::onComputerStartsNought() {
  setGameInProgress(true);
  set(ROWS /2, COLUMNS / 2, m_computerMark = Nought);
  m_humanMark = Cross;
  repaint();
}

void NaCWidget::onComputerStartsCross() {
  setGameInProgress(true);
  set(ROWS /2, COLUMNS / 2, m_computerMark = Cross);
  m_humanMark = Nought;
  repaint();
}

void NaCWidget::onHumanStartsNought() {
  setGameInProgress(true);
  m_computerMark = Cross;
  m_humanMark = Nought;
  repaint();
}

void NaCWidget::onHumanStartsCross() {
  setGameInProgress(true);
  m_computerMark = Nought;
  m_humanMark = Cross;
  repaint();
}

void NaCWidget::mouseMark(int row, int column) {
  set(row, column, m_humanMark);
  repaint();

  if (!checkWinner(row, column, m_humanMark)) {
/*    QTime stopTime = QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < stopTime) {
      // Empty.
    }*/

    calculateComputerMove(row, column);
    set(row, column, m_computerMark);
    checkWinner(row, column, m_computerMark);
    repaint();
  }
}

void NaCWidget::drawMark(QPainter& painter,
                         const QRect& markRect, int mark) {
  painter.setPen(Qt::black);

  switch (mark) {
    case Nought:
      painter.drawEllipse(markRect);
      break;

    case Cross:
      painter.drawLine(markRect.topLeft(),
                       markRect.bottomRight());
      painter.drawLine(markRect.topRight(),
                       markRect.bottomLeft());
      break;

    case Empty:
      break;
  }
}

bool NaCWidget::checkWinner(int row, int column, Mark mark) {
  if ((countMarks(row, column, -1, 0, mark) >= 5) ||
      (countMarks(row, column, 0, -1, mark) >= 5) ||
      (countMarks(row, column, -1, 1, mark) >= 5) ||
      (countMarks(row, column, 1, 1, mark) >= 5)) {
    QMessageBox messageBox(QMessageBox::Information,
                           tr("Victory"), QString());
    QString text;
    text.sprintf("The Winner: %s.",
                 (mark == m_computerMark) ? "Computer" : "Human");

    messageBox.setText(text);
    messageBox.setStandardButtons(QMessageBox::Ok);
    messageBox.exec();
    setGameInProgress(false);
    clearGrid();
    repaint();
    return true;
  }

  return false;
}

double NaCWidget::countMarks(int row, int column, int rowStep,
                        int columnStep, Mark mark) {
  double markCount = 0;
  int freeCount = 0;

  { bool marked = true;
    int currentRow = row, currentColumn = column;
    while ((currentRow >= 0) && (currentRow < ROWS) &&
           (currentColumn >= 0) && (currentColumn < COLUMNS)) {
      if (get(currentRow, currentColumn) == mark) {
        if (marked) {
          ++markCount;
        }
      }
      else if (get(currentRow, currentColumn) == Empty) {
        if (marked) {
          markCount += 0.4;
        }

        marked = false;
        ++freeCount;
      }
      else {
        break;
      }

      currentRow += rowStep;
      currentColumn += columnStep;
    }
  }

  { bool marked = true;
    int currentRow = row + rowStep,
        currentColumn = column + columnStep;
    while ((currentRow >= 0) && (currentRow < ROWS) &&
           (currentColumn >= 0) && (currentColumn < COLUMNS)) {
      if (get(currentRow, currentColumn) == mark) {
        if (marked) {
          ++markCount;
        }

        ++freeCount;
      }
      else if (get(currentRow, currentColumn) == Empty) {
        if (marked) {
          markCount += 0.4;
        }

        marked = false;
        ++freeCount;
      }
      else {
        break;
      }

      currentRow -= rowStep;
      currentColumn -= columnStep;
    }
  }

  --markCount;
  --freeCount;

  return (freeCount >= 5) ? markCount : 0;
}

void NaCWidget::calculateComputerMove(int& maxRow, int &maxColumn) {
  double maxComputerValue = 0, maxHumanValue = 0;
  QList<QPair<int,int>> maxComputerList, maxHumanList;

  for (int row = 0; row < ROWS; ++row) {
    for (int column = 0; column < COLUMNS; ++column)  {
      if (get(row, column) == Empty) {
        set(row, column, m_computerMark);

        { double computerValue =
            calculateMarkValue(row, column, m_computerMark);

          if (computerValue > maxComputerValue) {
            maxComputerValue = computerValue;
            maxComputerList.clear();
            maxComputerList.append(QPair<int,int>(row, column));
          }
          else if ((computerValue > 0) &&
                   (computerValue == maxComputerValue)) {
            maxComputerList.append(QPair<int,int>(row, column));
          }
        }

        set(row, column, m_humanMark);

        { double humanValue =
            calculateMarkValue(row, column, m_humanMark);

          if (humanValue > maxHumanValue) {
            maxHumanValue = humanValue;
            maxHumanList.clear();
            maxHumanList.append(QPair<int,int>(row, column));
          }
          else if ((humanValue > 0) &&
                   (humanValue == maxHumanValue)) {
            maxHumanList.append(QPair<int,int>(row, column));
          }
        }

        set(row, column, Empty);
      }
    }
  }

  assert(!maxComputerList.empty() && !maxHumanList.empty());

  if ((maxComputerValue >= 2) &&
      ((maxComputerValue >= maxHumanValue) ||
       (maxHumanValue < 3.8))) {
    srand(time(NULL));
    QPair<int,int> pair =
      maxComputerList[rand() % maxComputerList.size()];
    maxRow = pair.first;
    maxColumn = pair.second;
  }
  else {
    srand(time(NULL));
    QPair<int,int> pair =
      maxHumanList[rand() % maxHumanList.size()];
    maxRow = pair.first;
    maxColumn = pair.second;
  }
}

double NaCWidget::calculateMarkValue(int row, int column,
                                     Mark mark) {
  return qMax(qMax(countMarks(row, column, -1, 0, mark),
                   countMarks(row, column, 0, -1, mark)),
              qMax(countMarks(row, column, -1, 1, mark),
                   countMarks(row, column, 1, 1, mark)));
}
