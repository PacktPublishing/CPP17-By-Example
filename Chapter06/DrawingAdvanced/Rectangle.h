#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <FStream>
using namespace std;

#include "Figure.h"

class RectangleX : public Figure {
  public:
    RectangleX();
    virtual FigureId getId() const {return RectangleId;}

    RectangleX(const RectangleX& rectangle);
    Figure* clone() const;

    virtual void initializePoints(QPoint point);

    virtual bool isClick(QPoint mousePoint);
    virtual bool isInside(QRect rectangleArea);
    virtual void doubleClick(QPoint mousePoint);

    virtual void modify(QSize distance);
    virtual void move(QSize distance);

    virtual QRect area() const;
    virtual void draw(QPainter& painter) const;

    virtual bool write(ofstream& outStream) const;
    virtual bool read(ifstream& inStream);

  private:
    enum {TopLeftPoint, TopRightPoint, BottomRightPoint,
          BottomLeftPoint, MoveRectangle} m_rectangleMode;

  protected:
    QPoint m_topLeft, m_bottomRight;
};

#endif
