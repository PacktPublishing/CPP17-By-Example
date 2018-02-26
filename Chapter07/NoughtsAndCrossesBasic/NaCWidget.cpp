#include "NaCWidget.h"
#include <CTime>

NaCWidget::NaCWidget(QWidget* parentWidget)
 :GameWidget(ROWS, COLUMNS, parentWidget) {
  // Empty.
}

bool NaCWidget::isNoughtStartsEnabled() {
  return !isGameInProgress();
}

void NaCWidget::onNoughtStarts() {
  setGameInProgress(true);
  m_nextMark = Nought;
  update();
}

bool NaCWidget::isCrossStartsEnabled() {
  return !isGameInProgress();
}

void NaCWidget::onCrossStarts() {
  setGameInProgress(true);
  m_nextMark = Cross;
  update();
}

void NaCWidget::mouseMark(int row, int column) {
  set(row, column, m_nextMark);
  checkWinner(row, column, m_nextMark);
  m_nextMark = (m_nextMark == Nought) ? Cross : Nought;
  update();
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

void NaCWidget::checkWinner(int row, int column, Mark mark) {
  if ((countMarks(row, column, -1, 0, mark) >= 5) ||
      (countMarks(row, column, 0, -1, mark) >= 5) ||
      (countMarks(row, column, -1, 1, mark) >= 5) ||
      (countMarks(row, column, 1, 1, mark) >= 5)) {
    QMessageBox messageBox(QMessageBox::Information,
                           tr("Victory"), QString());
    QString text;
    text.sprintf("The Winner: %s.",
                 (mark == Nought) ? "Nought" : "Cross");

    messageBox.setText(text);
    messageBox.setStandardButtons(QMessageBox::Ok);
    messageBox.exec();
    clearGrid();

    setGameInProgress(false);
    update();
  }
}

int NaCWidget::countMarks(int row, int column, int rowStep,
                          int columnStep, Mark mark) {
  int countMarks = 0;

  { int currentRow = row, currentColumn = column;
    while ((currentRow >= 0) && (currentRow < ROWS) &&
           (currentColumn >= 0) && (currentColumn < COLUMNS) &&
           (get(currentRow, currentColumn) == mark)) {
      ++countMarks;
      currentRow += rowStep;
      currentColumn += columnStep;
    }
  }

  { int currentRow = row + rowStep,
        currentColumn = column + columnStep;
    while ((currentRow >= 0) && (currentRow < ROWS) &&
           (currentColumn >= 0) && (currentColumn < COLUMNS) &&
           (get(currentRow, currentColumn) == mark)) {
      ++countMarks;
      currentRow -= rowStep;
      currentColumn -= columnStep;
    }
  }

  return countMarks;
}
