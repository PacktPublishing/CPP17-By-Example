#include <CAssert>
#include "..\\MainWindow\\DocumentWidget.h"
#include "Rectangle.h"

RectangleX::RectangleX()
 :m_rectangleMode(BottomRightPoint) {
  // Empty.
}

RectangleX::RectangleX(const RectangleX& rectangle)
 :Figure(rectangle),
  m_topLeft(rectangle.m_topLeft),
  m_bottomRight(rectangle.m_bottomRight) {
  // Empty.
}

Figure* RectangleX::clone() const {
  RectangleX* rectanglePtr = new RectangleX(*this);
  assert(rectanglePtr != nullptr);
  return rectanglePtr;
}

void RectangleX::initializePoints(QPoint point) {
  m_topLeft = point;
  m_bottomRight = point;
}

bool RectangleX::isClick(QPoint mousePoint) {
  QRect topLeftRect(makeRect(m_topLeft, Tolerance));

  if (topLeftRect.contains(mousePoint)) {
    m_rectangleMode = TopLeftPoint;
    return true;
  }

  QPoint topRightPoint(m_bottomRight.x(), m_topLeft.y());
  QRect topRectRight(makeRect(topRightPoint, Tolerance));

  if (topRectRight.contains(mousePoint)) {
    m_rectangleMode = TopRightPoint;
    return true;
  }

  QRect m_bottomRightRect(makeRect(m_bottomRight, Tolerance));

  if (m_bottomRightRect.contains(mousePoint)) {
    m_rectangleMode = BottomRightPoint;
    return true;
  }

  QPoint bottomLeftPoint(m_topLeft.x(), m_bottomRight.y());
  QRect bottomLeftRect(makeRect(bottomLeftPoint, Tolerance));

  if (bottomLeftRect.contains(mousePoint)) {
    m_rectangleMode = BottomLeftPoint;
    return true;
  }

  QRect areaRect(m_topLeft, m_bottomRight);

  if (filled()) {
    if (areaRect.contains(mousePoint)) {
      m_rectangleMode = MoveRectangle;
      return true;
    }
  }
  else {
    QRect largeAreaRect(areaRect), smallAreaRect(areaRect);

    largeAreaRect += Tolerance;
    smallAreaRect -= Tolerance;

    if (largeAreaRect.contains(mousePoint) &&
        !smallAreaRect.contains(mousePoint)) {
      m_rectangleMode = MoveRectangle;
      return true;
    }
  }

  return false;
}

bool RectangleX::isInside(QRect area) {
  return area.contains(m_topLeft) &&
         area.contains(m_bottomRight);
}

void RectangleX::doubleClick(QPoint mousePoint) {
  if (isClick(mousePoint)) {
    filled() = !filled();
  }
}

void RectangleX::modify(QSize distance) {
  switch (m_rectangleMode) {
    case TopLeftPoint:
      m_topLeft += distance;
      break;

    case TopRightPoint:
      m_topLeft.setY(m_topLeft.y() + distance.height());
      m_bottomRight.setX(m_bottomRight.x() + distance.width());
      break;

    case BottomRightPoint:
      m_bottomRight += distance;
      break;

    case BottomLeftPoint:
      m_topLeft.setX(m_topLeft.x() + distance.width());
      m_bottomRight.setY(m_bottomRight.y() + distance.height());
      break;

    case MoveRectangle:
      move(distance);
      break;
  }
}

void RectangleX::move(QSize distance) {
  m_topLeft += distance;
  m_bottomRight += distance;
}

QRect RectangleX::area() const {
  QRect areaRect(m_topLeft, m_bottomRight);
  areaRect.normalized();

  if (marked()) {
    areaRect += Tolerance;
  }

  return areaRect;
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

  if (marked()) {
    painter.fillRect(makeRect(m_topLeft, Tolerance), Qt::black);
    QPoint topRight(m_bottomRight.x(), m_topLeft.y());
    painter.fillRect(makeRect(topRight, Tolerance), Qt::black);
    painter.fillRect(makeRect(m_bottomRight, Tolerance),
                     Qt::black);
    QPoint bottomLeft(m_topLeft.x(), m_bottomRight.y());
    painter.fillRect(makeRect(bottomLeft, Tolerance), Qt::black);
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
