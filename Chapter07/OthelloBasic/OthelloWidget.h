#ifndef OTHELLOWIDGET_H
#define OTHELLOWIDGET_H

#include "..\\MainWindow\\GameWidget.h"

#define ROWS    8
#define COLUMNS 8

enum Mark {Empty = 0, Black, White};

class OthelloWidget : public GameWidget {
  Q_OBJECT

  public:
    OthelloWidget(QWidget* parentWidget);

    void mouseMark(int row, int column);
    void drawMark(QPainter& painter,
                  const QRect& markRect, int mark);

  public slots:
    DEFINE_LISTENER(OthelloWidget, isBlackStartsEnabled);
    void onBlackStarts();

    DEFINE_LISTENER(OthelloWidget, isWhiteStartsEnabled);
    void onWhiteStarts();

  private:
    void checkWinner();
    void turn(int row, int column, Mark mark);
    void calculateMark(int row, int column, Mark mark,
                       QSet<QPair<int,int>>& resultSet);
    Mark m_nextMark;
};

#endif // OTHELLOWIDGET_H
