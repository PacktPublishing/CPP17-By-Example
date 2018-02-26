#include <CAssert>
#include "..\\MainWindow\\DocumentWidget.h"
#include "Rectangle.h"

RectangleX::RectangleX() {
  // Empty.
}

void RectangleX::initializePoints(QPoint point) {
  m_topLeft = point;
  m_bottomRight = point;
}

void RectangleX::setLastPoint(QPoint point) {
  m_bottomRight = point;
}

bool RectangleX::isClick(QPoint mousePoint) {
  QRect areaRect(m_topLeft, m_bottomRight);

  if (filled()) {
    return areaRect.contains(mousePoint);
  }
  else {
    QRect largeAreaRect(areaRect), smallAreaRect(areaRect);

    largeAreaRect += Tolerance;
    smallAreaRect -= Tolerance;

    return largeAreaRect.contains(mousePoint) &&
           !smallAreaRect.contains(mousePoint);
  }

  return false;
}

void RectangleX::move(QSize distance) {
  m_topLeft += distance;
  m_bottomRight += distance;
}

void RectangleX::draw(QPainter& painter) const {
  painter.setPen(color());

  if (filled()) {
    painter.fillRect(QRect(m_topLeft, m_bottomRight), color());
  }
  else {
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(m_topLeft, m_bottomRight));
  }
}

bool RectangleX::write(ofstream& outStream) const {
  Figure::write(outStream);
  writePoint(outStream, m_topLeft);
  writePoint(outStream, m_bottomRight);
  return ((bool) outStream);
}

bool RectangleX::read (ifstream& inStream) {
  Figure::read(inStream);
  readPoint(inStream, m_topLeft);
  readPoint(inStream, m_bottomRight);
  return ((bool) inStream);
}
