#ifndef FIGURE_H
#define FIGURE_H

enum FigureId {LineId, RectangleId, EllipseId};

#include <QtWidgets>
#include <FStream>
using namespace std;

class Figure {
  public:
    Figure();
    virtual FigureId getId() const = 0;
    virtual void initializePoints(QPoint point) = 0;
    virtual void setLastPoint(QPoint point) = 0;

    virtual bool isClick(QPoint mousePoint) = 0;
    virtual void move(QSize distance) = 0;
    virtual void draw(QPainter &painter) const = 0;

    virtual bool write(ofstream& outStream) const;
    virtual bool read(ifstream& inStream);

    const QColor& color() const {return m_color;}
    QColor& color() {return m_color;}

    virtual bool filled() const {return m_filled;}
    virtual bool& filled() {return m_filled;}

    static const int Tolerance;

  private:
    QColor m_color;
    bool m_marked = false, m_filled = false;
};

#endif
