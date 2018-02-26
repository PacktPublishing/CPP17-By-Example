#include "GameWidget.h"
#include <QApplication>
#include <CAssert>

GameWidget::GameWidget(int rows, int columns,
                       QWidget* parentWidget)
 :QWidget(parentWidget),
  m_rows(rows),
  m_columns(columns),
  m_gameGrid(new int[rows * columns]) {
  assert(rows > 0);
  assert(columns > 0);
  assert(m_gameGrid != nullptr);
  clearGrid();
}

int GameWidget::get(int row, int column) const {
  return m_gameGrid[(row * m_columns) + column];
}

void GameWidget::set(int row, int column, int value) {
  m_gameGrid[(row * m_columns) + column] = value;
}

void GameWidget::clearGrid() {
  for (int row = 0; row < m_rows; ++row) {
    for (int column = 0; column < m_columns; ++column) {
      set(row, column, 0);
    }
  }
}

bool GameWidget::isQuitEnabled() {
  return m_gameInProgress;
}

bool GameWidget::isQuitOk() {
  if (m_gameInProgress) {
    QMessageBox messageBox(QMessageBox::Warning,
                           tr("Quit"), QString());
    messageBox.setText(tr("Quit the Game."));
    messageBox.setInformativeText
                  (tr("Do you really want to quit the game?"));
    messageBox.setStandardButtons(QMessageBox::Yes |
                                  QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::No);
    return (messageBox.exec() == QMessageBox::Yes);
  }

  return true;
}

void GameWidget::onQuit() {
  if (isQuitOk()) {
    m_gameInProgress = false;
    clearGrid();
    update();
  }
}

void GameWidget::onExit() {
  if (isQuitOk()) {
    qApp->exit(0);
  }
}

void GameWidget::resizeEvent(QResizeEvent* eventPtr) {
  m_rowHeight = height() / (m_rows + 2);
  m_columnWidth = width() / (m_columns + 2);
  QWidget::resizeEvent(eventPtr);
  update();
}

void GameWidget::mousePressEvent(QMouseEvent* eventPtr) {
  if (m_gameInProgress && eventPtr->button() == Qt::LeftButton) {
    QPoint mousePoint = eventPtr->pos();
    mousePoint.setX(mousePoint.x() - m_columnWidth);
    mousePoint.setY(mousePoint.y() - m_rowHeight);

    int row = mousePoint.y() / m_rowHeight,
        column = mousePoint.x() / m_columnWidth;

    if ((row < m_rows) && (column < m_columns) &&
        (get(row, column) == 0)) {
      mouseMark(row, column);
      update();
    }
  }
}

void GameWidget::paintEvent(QPaintEvent* /*eventPtr*/) {
  if (m_gameInProgress) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    for (int row = 0; row < m_rows; ++row) {
      QString text;
      text.sprintf("%c", (char) (((int) 'A') + row));
      QRect charRect(0, (row + 1) * m_rowHeight,
                     m_columnWidth, m_rowHeight);
      painter.drawText(charRect, Qt::AlignCenter |
                       Qt::AlignHCenter, text);
    }

    for (int column = 0; column < m_columns; ++column) {
      QString text;
      text.sprintf("%i", column);
      QRect charRect((column + 1) * m_columnWidth, 0,
                     m_columnWidth, m_rowHeight);
      painter.drawText(charRect, Qt::AlignCenter |
                       Qt::AlignHCenter, text);
    }

    painter.save();
    painter.translate(m_columnWidth, m_rowHeight);

    for (int row = 0; row < m_rows; ++row) {
      for (int column = 0; column < m_columns; ++column) {
        QRect markRect(column * m_columnWidth, row * m_rowHeight,
                       m_columnWidth, m_rowHeight);
        painter.setPen(Qt::black);
        painter.drawRect(markRect);
        painter.fillRect(markRect, Qt::lightGray);
        drawMark(painter, markRect, get(row, column));
      }
    }

    painter.restore();
  }
}

void GameWidget::closeEvent(QCloseEvent* eventPtr) {
  if (isQuitOk()) {
    eventPtr->accept();
    qApp->exit(0);
  }
  else {
    eventPtr->ignore();
  }
}
