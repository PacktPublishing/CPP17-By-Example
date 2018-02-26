#include <CAssert>
#include "..\\MainWindow\\DocumentWidget.h"
#include "Line.h"

Line::Line() {
  // Empty.
}

void Line::initializePoints(QPoint point) {
  m_firstPoint = point;
  m_lastPoint = point;
}

void Line::setLastPoint(QPoint point) {
  m_lastPoint = point;
}

bool Line::isClick(QPoint mousePoint) {
  if (m_firstPoint.x() == m_lastPoint.x()) {
    QRect lineRect(m_firstPoint, m_lastPoint);
    lineRect.normalized();
    lineRect += Tolerance;
    return lineRect.contains(mousePoint);
  }
  else {
    QPoint leftPoint = (m_firstPoint.x() < m_lastPoint.x())
                       ? m_firstPoint : m_lastPoint,
           rightPoint = (m_firstPoint.x() < m_lastPoint.x())
                        ? m_lastPoint : m_firstPoint;

    if ((leftPoint.x() <= mousePoint.x()) &&
        (mousePoint.x() <= rightPoint.x())) {
      int lineWidth = rightPoint.x() - leftPoint.x(),
          lineHeight = rightPoint.y() - leftPoint.y();

      int diffWidth = mousePoint.x() - leftPoint.x(),
          diffHeight = mousePoint.y() - leftPoint.y();

      return (fabs(diffHeight - (((double) lineHeight) /
                   lineWidth) * diffWidth) <= Tolerance);
    }

    return false;
  }
}

void Line::move(QSize distance) {
  m_firstPoint += distance;
  m_lastPoint += distance;
}

void Line::draw(QPainter& painter) const {
  painter.setPen(color());
  painter.drawLine(m_firstPoint, m_lastPoint);
}

bool Line::write(ofstream& outStream) const {
  Figure::write(outStream);
  writePoint(outStream, m_firstPoint);
  writePoint(outStream, m_lastPoint);
  return ((bool) outStream);
}

bool Line::read(ifstream& inStream) {
  Figure::read(inStream);
  readPoint(inStream, m_firstPoint);
  readPoint(inStream, m_lastPoint);
  return ((bool) inStream);
}
