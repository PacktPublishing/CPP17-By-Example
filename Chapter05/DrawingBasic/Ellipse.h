#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Rectangle.h"

class EllipseX : public RectangleX {
  public:
    EllipseX();
    FigureId getId() const {return EllipseId;}

    bool isClick(QPoint mousePoint);
    void draw(QPainter& painter) const;
};

#endif
