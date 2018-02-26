#ifndef LINE_H
#define LINE_H

#include <FStream>
using namespace std;

#include "Figure.h"

class Line : public Figure {
  public:
    Line();
    FigureId getId() const {return LineId;}

    Line(const Line& line);
    Figure* clone() const;

    void initializePoints(QPoint point);
    bool isClick(QPoint mousePoint);
    bool isInside(QRect rectangleArea);
    void doubleClick(QPoint /* mousePoint */) {/* Empty. */}

    void modify(QSize distance);
    void move(QSize distance);

    QRect area() const;
    void draw(QPainter& painter) const;

    bool write(ofstream& outStream) const;
    bool read(ifstream& inStream);

  private:
    enum {FirstPoint, LastPoint, MoveLine} m_lineMode;
    QPoint m_firstPoint, m_lastPoint;

    static bool isPointInLine(QPoint m_firstPoint,
                              QPoint m_lastPoint, QPoint point);
};

#endif
