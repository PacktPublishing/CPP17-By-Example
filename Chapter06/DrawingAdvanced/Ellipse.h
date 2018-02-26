#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Rectangle.h"

class EllipseX : public RectangleX {
  public:
    EllipseX();
    FigureId getId() const {return EllipseId;}

    EllipseX(const EllipseX& ellipse);
    Figure* clone() const;

    bool isClick(QPoint mousePoint);
    void modify(QSize distance);
    void draw(QPainter& painter) const;

  private:
    enum {CreateEllipse, LeftPoint, TopPoint, RightPoint,
          BottomPoint, MoveEllipse} m_ellipseMode;
};

#endif
