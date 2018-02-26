#include <CAssert>
#include "..\\MainWindow\\DocumentWidget.h"
#include "Ellipse.h"

EllipseX::EllipseX() {
  // Empty.
}

bool EllipseX::isClick(QPoint mousePoint) {
  QRect normalRect(m_topLeft, m_bottomRight);
  normalRect.normalized();

  if (filled()) {
    QRegion normalEllipse(normalRect, QRegion::Ellipse);
    return normalEllipse.contains(mousePoint);
  }
  else {
    QRect largeRect(normalRect), smallRect(normalRect);
    largeRect += Tolerance;
    smallRect -= Tolerance;

    QRegion largeEllipse(largeRect, QRegion::Ellipse),
            smallEllipse(smallRect, QRegion::Ellipse);

    return (largeEllipse.contains(mousePoint) &&
            !smallEllipse.contains(mousePoint));
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
}
