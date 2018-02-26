#include <CAssert>
#include "..\\MainWindow\\DocumentWidget.h"
#include "Ellipse.h"

EllipseX::EllipseX()
 :m_ellipseMode(CreateEllipse) {
  // Empty.
}

EllipseX::EllipseX(const EllipseX& ellipse)
 :RectangleX(ellipse) {
  // Empty.
}

Figure* EllipseX::clone() const {
  EllipseX* ellipsePtr = new EllipseX(*this);
  assert(ellipsePtr != nullptr);
  return ellipsePtr;
}

bool EllipseX::isClick(QPoint mousePoint) {
  QPoint leftPoint(m_topLeft.x(),
                   (m_topLeft.y() + m_bottomRight.y()) / 2);
  QRect leftRect(makeRect(leftPoint, Tolerance));

  if (leftRect.contains(mousePoint)) {
    m_ellipseMode = LeftPoint;
    return true;
  }

  QPoint topPoint((m_topLeft.x() + m_bottomRight.x()) / 2,
                  m_topLeft.y());
  QRect topRect(makeRect(topPoint, Tolerance));

  if (topRect.contains(mousePoint)) {
    m_ellipseMode = TopPoint;
    return true;
  }

  QPoint rightPoint(m_bottomRight.x(),
                    (m_topLeft.y() + m_bottomRight.y()) / 2);
  QRect rightRect(makeRect(rightPoint, Tolerance));

  if (rightRect.contains(mousePoint)) {
    m_ellipseMode = RightPoint;
    return true;
  }

  QPoint bottomPoint((m_topLeft.x() + m_bottomRight.x()) / 2,
                     m_bottomRight.y());
  QRect bottomRect(makeRect(bottomPoint, Tolerance));

  if (bottomRect.contains(mousePoint)) {
    m_ellipseMode = BottomPoint;
    return true;
  }

  QRect normalRect(m_topLeft, m_bottomRight);
  normalRect.normalized();

  if (filled()) {
    QRegion normalEllipse(normalRect, QRegion::Ellipse);

    if (normalEllipse.contains(mousePoint)) {
      m_ellipseMode = MoveEllipse;
      return true;
    }
  }
  else {
    QRect largeRect(normalRect), smallRect(normalRect);
    largeRect += Tolerance;
    smallRect -= Tolerance;

    QRegion largeEllipse(largeRect, QRegion::Ellipse),
            smallEllipse(smallRect, QRegion::Ellipse);

    if (largeEllipse.contains(mousePoint) &&
        !smallEllipse.contains(mousePoint)) {
      m_ellipseMode = MoveEllipse;
      return true;
    }
  }

  return false;
}

void EllipseX::modify(QSize distance) {
  switch (m_ellipseMode) {
    case CreateEllipse:
      m_bottomRight += distance;
      break;

    case LeftPoint:
      m_topLeft.setX(m_topLeft.x() + distance.width());
      break;

    case RightPoint:
      m_bottomRight.setX(m_bottomRight.x() + distance.width());
      break;

    case TopPoint:
      m_topLeft.setY(m_topLeft.y() + distance.height());
      break;

    case BottomPoint:
      m_bottomRight.setY(m_bottomRight.y() + distance.height());
      break;

    case MoveEllipse:
      move(distance);
      break;
  }
}

void EllipseX::draw(QPainter& painter) const {
  painter.setPen(color());

  if (filled()) {
    painter.setBrush(color());
    painter.drawEllipse(QRect(m_topLeft, m_bottomRight));
  }
  else {
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(QRect(m_topLeft, m_bottomRight));
  }

  if (marked()) {
    QPoint leftPoint(m_topLeft.x(),
                     (m_topLeft.y() + m_bottomRight.y())/2);
    painter.fillRect(makeRect(leftPoint, Tolerance), Qt::black);

    QPoint topPoint((m_topLeft.x() + m_bottomRight.x()) / 2,
                    m_topLeft.y());
    painter.fillRect(makeRect(topPoint, Tolerance), Qt::black);

    QPoint rightPoint(m_bottomRight.x(),
                      (m_topLeft.y() + m_bottomRight.y()) / 2);
    painter.fillRect(makeRect(rightPoint, Tolerance), Qt::black);

    QPoint bottomPoint((m_topLeft.x() + m_bottomRight.x()) / 2,
                       m_bottomRight.y());
    painter.fillRect(makeRect(bottomPoint, Tolerance), Qt::black);
  }
}
