#ifndef LINE_H
#define LINE_H

#include <FStream>
using namespace std;

#include "Figure.h"

class Line : public Figure {
  public:
    Line();
    FigureId getId() const {return LineId;}

    void initializePoints(QPoint point);
    void setLastPoint(QPoint point);

    bool isClick(QPoint mousePoint);
    void move(QSize distance);
    void draw(QPainter& painter) const;

    bool write(ofstream& outStream) const;
    bool read(ifstream& inStream);

  private:
    QPoint m_firstPoint, m_lastPoint;
};

#endif
