#include <CAssert>
#include "..\\MainWindow\\DocumentWidget.h"
#include "Line.h"

Line::Line()
 :m_lineMode(LastPoint) {
  // Empty.
}

Line::Line(const Line& line)
 :Figure(line),
  m_firstPoint(line.m_firstPoint),
  m_lastPoint(line.m_lastPoint) {
  // Empty.
}

Figure* Line::clone() const {
  Line* linePtr = new Line(*this);
  assert(linePtr != nullptr);
  return linePtr;
}

void Line::initializePoints(QPoint point) {
  m_firstPoint = point;
  m_lastPoint = point;
}

bool Line::isClick(QPoint mousePoint) {
  QRect firstSquare(makeRect(m_firstPoint, Tolerance));

  if (firstSquare.contains(mousePoint)) {
    m_lineMode = FirstPoint;
    return true;
  }

  QRect lastSquare(makeRect(m_lastPoint, Tolerance));

  if (lastSquare.contains(mousePoint)) {
    m_lineMode = LastPoint;
    return true;
  }

  if (isPointInLine(m_firstPoint, m_lastPoint, mousePoint)) {
    m_lineMode = MoveLine;
    return true;
  }

  return false;
}

bool Line::isInside(QRect area) {
  return area.contains(m_firstPoint) &&
         area.contains(m_lastPoint);
}

bool Line::isPointInLine(QPoint m_firstPoint, QPoint m_lastPoint,
                         QPoint point) {
  if (m_firstPoint.x() == m_lastPoint.x()) {
    QRect lineRect(m_firstPoint, m_lastPoint);
    lineRect.normalized();
    lineRect += Tolerance;
    return lineRect.contains(point);
  }
  else {
      QPoint leftPoint = (m_firstPoint.x() < m_lastPoint.x())
                         ? m_firstPoint : m_lastPoint,
             rightPoint = (m_firstPoint.x() < m_lastPoint.x())
                         ? m_lastPoint : m_firstPoint;

      if ((leftPoint.x() <= point.x()) &&
          (point.x() <= rightPoint.x())) {
        int lineWidth = rightPoint.x() - leftPoint.x(),
            lineHeight = rightPoint.y() - leftPoint.y();

        int diffWidth = point.x() - leftPoint.x(),
            diffHeight = point.y() - leftPoint.y();

        double delta = fabs(diffHeight -
                 (diffWidth * ((double) lineHeight) / lineWidth));
        return (delta <= Tolerance);
      }

    return false;
  }
}

void Line::modify(QSize distance) {
  switch (m_lineMode) {
    case FirstPoint:
      m_firstPoint += distance;
      break;

    case LastPoint:
      m_lastPoint += distance;
      break;

    case MoveLine:
      move(distance);
      break;
  }
}

void Line::move(QSize distance) {
  m_firstPoint += distance;
  m_lastPoint += distance;
}

void Line::draw(QPainter& painter) const {
  painter.setPen(color());
  painter.drawLine(m_firstPoint, m_lastPoint);

  if (marked()) {
    painter.fillRect(makeRect(m_firstPoint, Tolerance),
                     Qt::black);
    painter.fillRect(makeRect(m_lastPoint, Tolerance),
                     Qt::black);
  }
}

QRect Line::area() const {
  QRect lineArea(m_firstPoint, m_lastPoint);
  lineArea.normalized();

  if (marked()) {
    lineArea += Tolerance;
  }

  return lineArea;
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
